//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "game.h"
#include "cell.h"

void Game::processHit(int x) {
    auto value = board_.value(x);

    if (Cell::isExplored(value) || Cell::flag(value)) {
        return;
    }

    if (gameStatus_ == Status::INITIAL) {
        board_.initialize(x);
        gameStatus_ = Status::IN_PROGRESS;
        callbacks_.onGameStatusChanged(x, gameStatus_);
    }

    if (Cell::mineNoFlag(value)) {
        gameStatus_ = Status::FAILURE;
        callbacks_.onGameStatusChanged(x, gameStatus_);
        return;
    }

    countMines(x);
    board_.countRemainingMines();

    const auto &newStatus = checkForGameStatus();
    if (newStatus != gameStatus_) {
        gameStatus_ = newStatus;
        callbacks_.onGameStatusChanged(x, newStatus);
    }
}

void Game::toggleFlag(int x) {
    auto newValue = board_.toggleFlag(x);
    callbacks_.onCellChanged(x, newValue);

    if (gameStatus_ != Status::INITIAL) {
        const auto &newStatus = checkForGameStatus();
        if (newStatus != gameStatus_) {
            gameStatus_ = newStatus;
            callbacks_.onGameStatusChanged(x, newStatus);
        }
    }
}

void Game::countMines(int x) {
    auto result = board_.countMines(x);
    callbacks_.onCellChanged(x, result.value);
    if (result.value == 0) {
        for (auto neighbour : result.neighbours) {
            if (neighbour < 0) {
                break;
            }
            if (Cell::empty(board_.value(neighbour))) {
                countMines(neighbour);
            }
        }
    }
}
