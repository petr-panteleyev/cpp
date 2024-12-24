//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef GAMESCORE_H
#define GAMESCORE_H

#include "boardsize.h"
#include <QDate>

struct GameScore {
    BoardSize boardSize;
    QDate date;
    QTime time;

    bool operator==(const GameScore &) const = default;
    bool operator<(const GameScore &that) const { return this->time < that.time; }
};

#endif // GAMESCORE_H
