/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "mainwindow.h"
#include "boardsize.h"
#include "buttoneventfilter.h"
#include "cell.h"
#include "picture.h"
#include "qcolor.h"
#include "qgridlayout.h"
#include "qmessagebox.h"
#include "qnamespace.h"
#include "scoreboarddialog.h"
#include "settings.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <iterator>
#include <ranges>
#include <stdexcept>
#include "version.h"

static constexpr int CELL_SIZE{40};
static constexpr QSize IMAGE_SIZE{24, 24};

static constexpr QSize BUTTON_SIZE{CELL_SIZE, CELL_SIZE};

static const QString STYLE_RED{"color: red"};
static const QString STYLE_BLACK{"color: black"};

static const QIcon EMPTY_ICON;

static const QString ABOUT_TEXT = R"(
<h1>Sapper</h1>
<h2>Sapper %1</h2>
Built on %2<br>
Copyright &copy; 2024 Petr Panteleyev
)";

static std::array<QColor, 9> NUMBER_COLORS{
    QColorConstants::White, // unused
    QColorConstants::Blue,        QColorConstants::DarkGreen,        QColorConstants::Red,   QColorConstants::DarkBlue,
    QColor::fromRgb(165, 42, 42), QColor::fromRgb(0x00, 0x80, 0x80), QColorConstants::Black, QColorConstants::Gray};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), game_{*this}, eventFilter_{this}, boardSize_{BoardSize::BIG},
      buttonFont_{"Mine-Sweeper", 14, QFont::Medium}, lcdFont_{"Neat LCD", 20, QFont::Medium},
      scoreBoardDialog_{this, scoreBoard_}, boardSizeDialog_{this}, resultsAction_{tr("Results")},
      customGameMenu_{tr("Custom")}, newCustomGameAction_{tr("New...")} {
    ui->setupUi(this);

    scoreBoard_.load();

    ui->lcdMineCount->setFont(lcdFont_);
    ui->lcdMineCount->setStyleSheet(STYLE_RED);

    ui->lcdTimer->setFont(lcdFont_);
    ui->lcdTimer->setStyleSheet(STYLE_RED);

    ui->controlButton->setIcon(Picture::SMILING_FACE.icon());
    connect(ui->controlButton, &QPushButton::clicked, [this]() { newGame(boardSize_); });

    auto index = 0;
    for (auto row = 0; row < BoardSize::MAX_HEIGHT; ++row) {
        for (auto column = 0; column < BoardSize::MAX_WIDTH; ++column) {
            auto button = new QPushButton();
            button->setFixedSize(BUTTON_SIZE);
            button->setCheckable(true);
            button->setFont(buttonFont_);

            button->installEventFilter(&eventFilter_);

            buttons_[index++] = button;
            ui->buttonGrid->addWidget(button, row, column);
        }
    }

    connect(ui->actionExit, &QAction::triggered, [this]() { close(); });
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onHelpAbout);
    connect(&gameTimer_, &GameTimer::timeString, [this](const QString &text) { ui->lcdTimer->setText(text); });
    connect(&boardSizeDialog_, &QDialog::accepted, [this]() { newGame(boardSizeDialog_.boardSize()); });
    connect(&newCustomGameAction_, &QAction::triggered, this, &MainWindow::onNewCustomGame);   

    setupGameMenu();
    newGame(Settings::getLastBoardSize());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupGameMenu() {
    for (const BoardSize &size : BoardSize::STANDARD_SIZES) {
        auto action = new QAction(size.toString());
        ui->menuGame->addAction(action);
        connect(action, &QAction::triggered, [this, &size]() { newGame(size); });
    }

    ui->menuGame->addSeparator();
    ui->menuGame->addMenu(&customGameMenu_);

    buildCustomGameMenu();

    ui->menuGame->addSeparator();
    ui->menuGame->addAction(&resultsAction_);
    connect(&resultsAction_, &QAction::triggered, [this]() {
        scoreBoardDialog_.setup();
        scoreBoardDialog_.show();
    });
}

void MainWindow::newGame(const BoardSize &boardSize) {
    gameTimer_.stop();
    gameTimer_.reset();

    eventFilter_.setDisabled(false);
    ui->controlButton->setIcon(Picture::SMILING_FACE.icon());

    boardSize_ = boardSize;
    game_.newGame(boardSize);

    points_.fill(-1);

    for (auto button : buttons_) {
        button->setVisible(false);
    }

    for (auto row = 0; row < boardSize.height(); ++row) {
        for (auto column = 0; column < boardSize.width(); ++column) {
            auto index = row * BoardSize::MAX_WIDTH + column;
            auto button = buttons_[index];
            button->setVisible(true);
            button->setEnabled(true);
            button->setChecked(false);
            button->setText(nullptr);
            button->setIcon(EMPTY_ICON);
            button->setStyleSheet(STYLE_BLACK);

            points_[index] = row * boardSize.width() + column;
        }
    }

    ui->lcdMineCount->setText(QString::number(boardSize.mines()));

    this->adjustSize();
    setFixedSize(this->width(), this->height());

    Settings::setLastBoardSize(boardSize);
}

void MainWindow::onButtonClicked(QPushButton *button, QMouseEvent *event) {
    if (game_.gameStatus().isFinal()) {
        return;
    }

    auto found = std::find(buttons_.begin(), buttons_.end(), button);
    if (found == buttons_.end()) {
        return;
    }
    auto index = std::distance(buttons_.begin(), found);
    auto hitPoint = points_.at(index);

    if (event->button() == Qt::LeftButton) {
        game_.processHit(hitPoint);
    } else {
        game_.toggleFlag(hitPoint);
    }
    ui->lcdMineCount->setText(QString::number(game_.remainingMines()));
}

int MainWindow::hitPointToButtonIndex(int hitPoint) {
    auto hitPointPtr = std::find(points_.begin(), points_.end(), hitPoint);
    if (hitPointPtr == points_.end()) {
        throw std::runtime_error("Button not found");
    }
    return std::distance(points_.begin(), hitPointPtr);
}

void MainWindow::onCellChanged(int x, int newValue) {
    int index = hitPointToButtonIndex(x);
    auto button = buttons_[index];

    if (Cell::flag(newValue)) {
        button->setText(nullptr);
        button->setIcon(Picture::RED_FLAG.icon());
        button->setIconSize(IMAGE_SIZE);
    } else if (Cell::isExplored(newValue)) {
        button->setIcon(EMPTY_ICON);
        button->setChecked(true);
        button->setDisabled(true);

        if (newValue == 0) {
            button->setText(nullptr);
        } else {
            button->setText(QString::number(newValue));
            button->setStyleSheet("color: " + NUMBER_COLORS[newValue].name());
        }
    } else {
        button->setText(nullptr);
        button->setIcon(EMPTY_ICON);
    }
}

void MainWindow::onGameStatusChanged(int x, const GameStatus &newStatus) {
    if (newStatus == GameStatus::SUCCESS) {
        renderSuccess();
    } else if (newStatus == GameStatus::FAILURE) {
        renderFailure(x);
    } else if (newStatus == GameStatus::IN_PROGRESS) {
        gameTimer_.start();
    }
}

void MainWindow::renderSuccess() {
    gameTimer_.stop();

    eventFilter_.setDisabled(true);
    ui->controlButton->setIcon(Picture::LAUGHING_FACE.icon());

    auto gameScore = GameScore{.boardSize = boardSize_, .date = QDate::currentDate(), .time = gameTimer_.localTime()};
    auto top = scoreBoard_.add(gameScore);
    scoreBoard_.save();

    buildCustomGameMenu();

    if (top) {
        scoreBoardDialog_.setup();
        scoreBoardDialog_.show();
    }
}

void MainWindow::renderFailure(int clickPoint) {
    eventFilter_.setDisabled(true);

    gameTimer_.stop();
    ui->controlButton->setIcon(Picture::SAD_FACE.icon());

    for (int x = 0; x < game_.size(); x++) {
        auto value = game_.value(x);
        auto button = buttons_[hitPointToButtonIndex(x)];

        if (x == clickPoint) {
            button->setText("*");
            button->setStyleSheet(STYLE_RED);
        } else {
            if (Cell::emptyWithFlag(value)) {
                button->setText(nullptr);
                button->setIcon(Picture::BLACK_FLAG.icon());
            }

            if (Cell::mineNoFlag(value)) {
                button->setText("*");
                button->setIcon(EMPTY_ICON);
            }
        }
    }
}

void MainWindow::onNewCustomGame() {
    boardSizeDialog_.show();
}

void MainWindow::buildCustomGameMenu() {
    customGameMenu_.clear();
    customGameMenu_.addAction(&newCustomGameAction_);

    auto sizes = scoreBoard_.boardSizes();
    auto filteredSizes =
        sizes | std::views::filter([](const auto &s) { return !BoardSize::STANDARD_SIZES.contains(s); });

    if (!filteredSizes.empty()) {
        customGameMenu_.addSeparator();
        for (const auto &customSize : filteredSizes) {
            auto action = new QAction(customSize.toString(), &customGameMenu_);
            customGameMenu_.addAction(action);
            connect(action, &QAction::triggered, [this, customSize]() { newGame(customSize); });
        }
    }
}

void MainWindow::onHelpAbout() {
    auto text = QString(ABOUT_TEXT)
            .arg(QString::fromStdString(Version::projectVersion))
            .arg(QString::fromStdString(Version::buildDate));
    QMessageBox::about(this, tr("About Sapper"), text);
}
