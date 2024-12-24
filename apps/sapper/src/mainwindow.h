//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boardsize.h"
#include "boardsizedialog.h"
#include "buttoneventfilter.h"
#include "game.h"
#include "gametimer.h"
#include "qfont.h"
#include "scoreboard.h"
#include "scoreboarddialog.h"
#include <QMainWindow>
#include <QMenu>

namespace Ui {
class MainWindow;
}

class QPushButton;

class MainWindow final : public QMainWindow, GameCallbackHandler, GameTimerHandler {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onButtonClicked(QPushButton *button, QMouseEvent *event);

    virtual void onCellChanged(int x, int newValue) override;
    virtual void onGameStatusChanged(int x, const Game::Status &newStatus) override;
    virtual void onTimerUpdate(QTime time) override;

  private:
    void newGame(const BoardSize &boardSize);
    void setupGameMenu();
    void renderSuccess();
    void renderFailure(int hitPoint);
    int hitPointToButtonIndex(int hitPoint);
    void onNewCustomGame();
    void buildCustomGameMenu();
    void onHelpAbout();

  private:
    Ui::MainWindow *ui;

    Game game_;
    ScoreBoard scoreBoard_;

    std::array<QPushButton *, BoardSize::BOARD_ARRAY_SIZE> buttons_;
    std::array<int, BoardSize::BOARD_ARRAY_SIZE> points_;

    ButtonEventFilter eventFilter_;
    BoardSize boardSize_;
    QFont buttonFont_;
    QFont lcdFont_;
    GameTimer gameTimer_;

    ScoreBoardDialog scoreBoardDialog_;
    BoardSizeDialog boardSizeDialog_;
};

#endif // MAINWINDOW_H
