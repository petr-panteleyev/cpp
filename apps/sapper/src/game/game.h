/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "callbacks.h"
#include "gamestatus.h"

class Game final {
  public:
    explicit Game(GameCallbackHandler &callbacks) : gameStatus_{GameStatus::INITIAL}, callbacks_{callbacks} {};

    const GameStatus &gameStatus() const noexcept { return gameStatus_; }

    int remainingMines() const noexcept { return board_.remainingMines(); }
    int size() const noexcept { return board_.size(); }
    int value(int x) const noexcept { return board_.value(x); }

    void processHit(int x);
    void toggleFlag(int x);

    void newGame(const BoardSize &boardSize) {
        board_.setup(boardSize);
        gameStatus_ = GameStatus::INITIAL;
    }

  private:
    const GameStatus &checkForGameStatus() const {
        return board_.hasUnexploredCells() ? GameStatus::IN_PROGRESS : GameStatus::SUCCESS;
    }
    void countMines(int x);

  private:
    Board                board_;
    GameStatusRef        gameStatus_;
    GameCallbackHandler &callbacks_;
};

#endif // GAME_H
