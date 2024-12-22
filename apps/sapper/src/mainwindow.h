/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "boardsize.h"
#include "buttoneventfilter.h"
#include "callbacks.h"
#include "game.h"
#include "gametimer.h"
#include "qfont.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QPushButton;

class MainWindow : public QMainWindow, GameCallbackHandler {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onButtonClicked(QPushButton *button, QMouseEvent *event);

    virtual void onCellChanged(int x, int newValue) override;
    virtual void onGameStatusChanged(int x, const GameStatus &newStatus) override;

  private:
    void newGame(const BoardSize &boardSize);
    void setupGameMenu();
    void renderSuccess();
    void renderFailure(int hitPoint);
    int  hitPointToButtonIndex(int hitPoint);

  private:
    Ui::MainWindow *ui;

    Game game_;

    std::array<QPushButton *, BoardSize::BOARD_ARRAY_SIZE> buttons_;
    std::array<int, BoardSize::BOARD_ARRAY_SIZE>           points_;

    ButtonEventFilter eventFilter_;
    BoardSize         boardSize_;
    QFont             buttonFont_;
    QFont             lcdFont_;
    GameTimer         gameTimer_;
};

#endif // MAINWINDOW_H