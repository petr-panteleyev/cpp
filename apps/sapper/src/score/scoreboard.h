/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "boardsize.h"
#include <QDate>
#include <set>
#include <vector>

struct GameScore {
    BoardSize boardSize;
    QDate date;
    QTime time;

    bool operator==(const GameScore &) const = default;
    bool operator<(const GameScore &that) const { return this->time < that.time; }
};

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

#endif // SCOREBOARD_H
