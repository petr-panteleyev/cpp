//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef SETTINGS_H
#define SETTINGS_H

#include "boardsize.h"
#include "scoreboard.h"
#include <span>

namespace Settings {

void setLastBoardSize(const BoardSize &boardSize);
BoardSize getLastBoardSize();

void setGameScores(const std::span<GameScore> &scores);
std::vector<GameScore> getGameScores();

} // namespace Settings

#endif // SETTINGS_H
