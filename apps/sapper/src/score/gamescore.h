//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "boardsize.h"
#include <QDate>

struct GameScore {
    BoardSize boardSize;
    QDate date;
    QTime time;

    bool operator==(const GameScore &) const = default;
    bool operator<(const GameScore &that) const { return this->time < that.time; }
};
