//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef GAME_H
#define GAME_H

#include "board.h"

class GameCallbackHandler;

class Game final {
  public:
    enum class Status {
        INITIAL,
        IN_PROGRESS,
        SUCCESS,
        FAILURE,
    };

  public:
    explicit Game(GameCallbackHandler &callbacks) : gameStatus_{Status::INITIAL}, callbacks_{callbacks} {};

    bool finished() const noexcept { return gameStatus_ == Status::SUCCESS || gameStatus_ == Status::FAILURE; }

    int remainingMines() const noexcept { return board_.remainingMines(); }
    int size() const noexcept { return board_.size(); }
    int value(int x) const noexcept { return board_.value(x); }

    void processHit(int x);
    void toggleFlag(int x);

    void newGame(const BoardSize &boardSize) {
        board_.setup(boardSize);
        gameStatus_ = Status::INITIAL;
    }

  private:
    const Status checkForGameStatus() const {
        return board_.hasUnexploredCells() ? Status::IN_PROGRESS : Status::SUCCESS;
    }
    void countMines(int x);

  private:
    Board board_;
    Status gameStatus_;
    GameCallbackHandler &callbacks_;
};

class GameCallbackHandler {
  public:
    virtual void onCellChanged(int x, int newValue) = 0;
    virtual void onGameStatusChanged(int x, const Game::Status &newStatus) = 0;
};

#endif // GAME_H
