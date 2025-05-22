//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "mainwindow.h"
#include "boardsize.h"
#include "boardsizedialog.h"
#include "buttoneventfilter.h"
#include "cell.h"
#include "pictures.h"
#include "scoreboarddialog.h"
#include "settings.h"
#include "ui_mainwindow.h"
#include "version.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <ranges>

static constexpr int CELL_SIZE{40};
static constexpr QSize IMAGE_SIZE{24, 24};

static constexpr QSize BUTTON_SIZE{CELL_SIZE, CELL_SIZE};

static const QString STYLE_RED{"color: red"};
static const QString STYLE_BLACK{"color: black"};

static const QIcon EMPTY_ICON;

static const QString ABOUT_TEXT = R"(
<h1>Сапёр</h1>
<table border='0'>
<tr><td>Версия:<td>%1
<tr><td>Дата сборки:<td>%2
</table>
Copyright &copy; 2024 Petr Panteleyev
)";

static std::array<QColor, 9> NUMBER_COLORS{
    QColorConstants::White, // unused
    QColorConstants::Blue,        QColorConstants::DarkGreen,        QColorConstants::Red,   QColorConstants::DarkBlue,
    QColor::fromRgb(165, 42, 42), QColor::fromRgb(0x00, 0x80, 0x80), QColorConstants::Black, QColorConstants::Gray};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui{std::make_unique<Ui::MainWindow>()}, game_{*this}, eventFilter_{this},
      boardSize_{BoardSize::BIG}, buttonFont_{"Mine-Sweeper", 14, QFont::Medium},
      lcdFont_{"Neat LCD", 20, QFont::Medium}, gameTimer_{*this},
      scoreBoardDialog_{new ScoreBoardDialog{this, scoreBoard_}}, boardSizeDialog_{new BoardSizeDialog{this}} {
    ui->setupUi(this);

    scoreBoard_.load();

    ui->lcdMineCount->setFont(lcdFont_);
    ui->lcdMineCount->setStyleSheet(STYLE_RED);

    ui->lcdTimer->setFont(lcdFont_);
    ui->lcdTimer->setStyleSheet(STYLE_RED);

    ui->controlButton->setIcon(Pictures::icon(Picture::SMILING_FACE));
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
    connect(boardSizeDialog_, &QDialog::accepted, [this]() { newGame(boardSizeDialog_->boardSize()); });
    connect(ui->actionNewCustomGame, &QAction::triggered, [this]() { boardSizeDialog_->show(); });

    setupGameMenu();
    newGame(Settings::getLastBoardSize());
}

MainWindow::~MainWindow() {
}

void MainWindow::setupGameMenu() {
    ui->actionBigGame->setText(BoardSize::BIG.toString());
    connect(ui->actionBigGame, &QAction::triggered, [this]() { newGame(BoardSize::BIG); });
    ui->actionMediumGame->setText(BoardSize::MEDIUM.toString());
    connect(ui->actionMediumGame, &QAction::triggered, [this]() { newGame(BoardSize::MEDIUM); });
    ui->actionSmallGame->setText(BoardSize::SMALL.toString());
    connect(ui->actionSmallGame, &QAction::triggered, [this]() { newGame(BoardSize::SMALL); });

    buildCustomGameMenu();

    connect(ui->actionResults, &QAction::triggered, [this]() {
        scoreBoardDialog_->setup();
        scoreBoardDialog_->show();
    });
}

void MainWindow::newGame(const BoardSize &boardSize) {
    gameTimer_.stop();
    gameTimer_.reset();

    eventFilter_.setDisabled(false);
    ui->controlButton->setIcon(Pictures::icon(Picture::SMILING_FACE));

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
    if (game_.finished()) {
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
        button->setIcon(Pictures::icon(Picture::RED_FLAG));
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

void MainWindow::onGameStatusChanged(int x, const Game::Status &newStatus) {
    if (newStatus == Game::Status::SUCCESS) {
        renderSuccess();
    } else if (newStatus == Game::Status::FAILURE) {
        renderFailure(x);
    } else if (newStatus == Game::Status::IN_PROGRESS) {
        gameTimer_.start();
    }
}

void MainWindow::onTimerUpdate(QTime time) {
    ui->lcdTimer->setText(time.toString("mm:ss"));
}

void MainWindow::renderSuccess() {
    gameTimer_.stop();

    eventFilter_.setDisabled(true);
    ui->controlButton->setIcon(Pictures::icon(Picture::LAUGHING_FACE));

    auto gameScore = GameScore{.boardSize = boardSize_, .date = QDate::currentDate(), .time = gameTimer_.localTime()};
    auto top = scoreBoard_.add(gameScore);
    scoreBoard_.save();

    buildCustomGameMenu();

    if (top) {
        scoreBoardDialog_->setup();
        scoreBoardDialog_->show();
    }
}

void MainWindow::renderFailure(int clickPoint) {
    eventFilter_.setDisabled(true);

    gameTimer_.stop();
    ui->controlButton->setIcon(Pictures::icon(Picture::SAD_FACE));

    for (int x = 0; x < game_.size(); x++) {
        auto value = game_.value(x);
        auto button = buttons_[hitPointToButtonIndex(x)];

        if (x == clickPoint) {
            button->setText("*");
            button->setStyleSheet(STYLE_RED);
        } else {
            if (Cell::emptyWithFlag(value)) {
                button->setText(nullptr);
                button->setIcon(Pictures::icon(Picture::BLACK_FLAG));
            }

            if (Cell::mineNoFlag(value)) {
                button->setText("*");
                button->setIcon(EMPTY_ICON);
            }
        }
    }
}

void MainWindow::buildCustomGameMenu() {
    auto menu = ui->customGameMenu;

    auto actions = menu->actions();
    for (auto index = 1; index < actions.count(); ++index) {
        menu->removeAction(actions.at(index));
    }

    auto sizes = scoreBoard_.boardSizes();
    auto filteredSizes =
        sizes | std::views::filter([](const auto &s) { return !BoardSize::STANDARD_SIZES.contains(s); });

    if (!filteredSizes.empty()) {
        menu->addSeparator();
        for (const auto &customSize : filteredSizes) {
            auto action = new QAction(customSize.toString(), menu);
            menu->addAction(action);
            connect(action, &QAction::triggered, [this, customSize]() { newGame(customSize); });
        }
    }
}

void MainWindow::onHelpAbout() {
    auto text = QString(ABOUT_TEXT)
                    .arg(QString::fromStdString(Version::projectVersion))
                    .arg(QString::fromStdString(Version::buildDate));
    QMessageBox::about(this, "О программе", text);
}
