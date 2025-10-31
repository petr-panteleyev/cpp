//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include <chrono>
#include <set>

module apps.sapper.scoreboard;

namespace {

constexpr int TOP_SIZE = 10;

}

bool ScoreBoard::add(const GameScore &score) {
    auto current = scores(score.boardSize_);

    if (current.empty()) {
        scores_.push_back(score);
        return true;
    }

    auto newTop = score.seconds_ < current.begin()->seconds_;

    if (current.size() < TOP_SIZE) {
        scores_.push_back(score);
        return newTop;
    }

    auto last = *current.rbegin();
    if (score.seconds_ < last.seconds_) {
        std::erase(scores_, last);
        scores_.push_back(score);
        return newTop;
    }

    return false;
}

ScoreBoard::ScoreBoard() {
}

std::set<BoardSize> ScoreBoard::boardSizes() const {
    std::set<BoardSize> result;
    for (const auto &sc : scores_) {
        result.insert(sc.boardSize_);
    }
    return result;
}

std::set<GameScore> ScoreBoard::scores(const BoardSize &boardSize) const {
    std::set<GameScore> result;
    for (const auto &sc : scores_) {
        if (sc.boardSize_ == boardSize) {
            result.insert(sc);
        }
    }
    return result;
}
