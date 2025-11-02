//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include <functional>

export module apps.sapper.game;

import apps.sapper.board;
import apps.sapper.boardsize;

export enum class GameStatus {
    INITIAL,
    IN_PROGRESS,
    SUCCESS,
    FAILURE,
};

export class Game final {
  public:
    explicit Game(const std::function<void(int, int)> &cellChangedCallback,
                  const std::function<void(int, GameStatus)> &gameStatusChangedCallback)
        : gameStatus_{GameStatus::INITIAL}, cellChangedCallback_{cellChangedCallback},
          gameStatusChangedCallback_{gameStatusChangedCallback} {}

    bool finished() const noexcept { return gameStatus_ == GameStatus::SUCCESS || gameStatus_ == GameStatus::FAILURE; }

    int remainingMines() const noexcept { return board_.remainingMines(); }
    int size() const noexcept { return board_.size(); }
    int value(int x) const noexcept { return board_.value(x); }

    void processHit(int x);
    void toggleFlag(int x);
    void newGame(const BoardSize &boardSize);

  private:
    const GameStatus checkForGameStatus() const {
        return board_.hasUnexploredCells() ? GameStatus::IN_PROGRESS : GameStatus::SUCCESS;
    }

    void countMines(int x);

  private:
    Board board_;
    GameStatus gameStatus_;

    std::function<void(int, int)> cellChangedCallback_;
    std::function<void(int, GameStatus)> gameStatusChangedCallback_;
};
