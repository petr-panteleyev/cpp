//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "boardsize.hpp"
#include "gamescore.hpp"
#include <set>
#include <vector>

class ScoreBoard {
  public:
    ScoreBoard() {}

    bool add(const GameScore &score);

    std::set<BoardSize> boardSizes() const;

    const std::vector<GameScore> &scores() const { return scores_; }

    std::set<GameScore> scores(const BoardSize &boardSize) const;
    void setScores(const std::vector<GameScore> &scores) { scores_ = scores; }

  private:
    std::vector<GameScore> scores_;
};
