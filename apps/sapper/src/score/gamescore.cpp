//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "gamescore.h"

import libs.common.localdate;

GameScore::GameScore(const BoardSize &boardSize, const std::chrono::seconds &seconds)
    : boardSize_{boardSize}, date_{LocalDate::now()}, seconds_{seconds} {
}
