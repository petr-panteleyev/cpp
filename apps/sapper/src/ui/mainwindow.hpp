//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "buttoneventfilter.hpp"
#include "game.hpp"
#include "gametimer.hpp"
#include "scoreboard.hpp"
#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}
class BoardSizeDialog;
class ScoreBoardDialog;

class MainWindow final : public QMainWindow {
  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onButtonClicked(QPushButton *button, QMouseEvent *event);

    void onTimerUpdate(std::chrono::seconds seconds);

  private:
    void onCellChanged(int x, int newValue);
    void onGameStatusChanged(int x, GameStatus newStatus);

    void newGame(const BoardSize &boardSize);
    void setupGameMenu();
    void renderSuccess();
    void renderFailure(int hitPoint);
    int hitPointToButtonIndex(int hitPoint);
    void buildCustomGameMenu();
    void onHelpAbout();

  private:
    std::unique_ptr<Ui::MainWindow> ui;

    Game game_;
    ScoreBoard scoreBoard_;

    std::array<QPushButton *, BoardSize::BOARD_ARRAY_SIZE> buttons_;
    std::array<int, BoardSize::BOARD_ARRAY_SIZE> points_;

    ButtonEventFilter eventFilter_;
    BoardSize boardSize_;
    QFont buttonFont_;
    QFont lcdFont_;
    GameTimer gameTimer_;

    ScoreBoardDialog *scoreBoardDialog_;
    BoardSizeDialog *boardSizeDialog_;
};
