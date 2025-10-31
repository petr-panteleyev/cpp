//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include <span>
#include <vector>

export module apps.sapper.settings;

import apps.sapper.boardsize;
import apps.sapper.gamescore;

export namespace Settings {

void setLastBoardSize(const BoardSize &boardSize);
BoardSize getLastBoardSize();

void setGameScores(const std::span<GameScore> &scores);
std::vector<GameScore> getGameScores();

} // namespace Settings
