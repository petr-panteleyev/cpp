//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "scoreboard.h"
#include "boardsize.h"
#include "settings.h"

constexpr int TOP_SIZE = 10;

bool ScoreBoard::add(const GameScore &score) {
    auto current = scores(score.boardSize);

    if (current.empty()) {
        scores_.push_back(score);
        return true;
    }

    auto newTop = score.time < current.begin()->time;

    if (current.size() < TOP_SIZE) {
        scores_.push_back(score);
        return newTop;
    }

    auto last = *current.rbegin();
    if (score.time < last.time) {
        std::erase(scores_, last);
        scores_.push_back(score);
        return newTop;
    }

    return false;
}

ScoreBoard::ScoreBoard() {
}

void ScoreBoard::save() {
    Settings::setGameScores(scores_);
}

void ScoreBoard::load() {
    scores_ = Settings::getGameScores();
}

std::set<BoardSize> ScoreBoard::boardSizes() const {
    std::set<BoardSize> result;
    for (const auto &sc : scores_) {
        result.insert(sc.boardSize);
    }
    return result;
}

std::set<GameScore> ScoreBoard::scores(const BoardSize &boardSize) const {
    std::set<GameScore> result;
    for (const auto &sc : scores_) {
        if (sc.boardSize == boardSize) {
            result.insert(sc);
        }
    }
    return result;
}
