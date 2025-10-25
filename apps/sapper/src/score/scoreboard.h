//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "gamescore.h"

class ScoreBoard {
  public:
    ScoreBoard();

    bool add(const GameScore &score);

    std::set<BoardSize> boardSizes() const;
    std::set<GameScore> scores(const BoardSize &boardSize) const;

    void save();
    void load();

  private:
    std::vector<GameScore> scores_;
};
