//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "boardsize.hpp"
#include "gamescore.hpp"
#include <span>
#include <vector>

namespace Settings {

void setLastBoardSize(const BoardSize &boardSize);
BoardSize getLastBoardSize();

void setGameScores(const std::span<GameScore> &scores);
std::vector<GameScore> getGameScores();

} // namespace Settings
