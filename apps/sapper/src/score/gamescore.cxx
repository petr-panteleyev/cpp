//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include <chrono>

export module apps.sapper.gamescore;

import apps.sapper.boardsize;
import libs.common.localdate;

export struct GameScore final {
    BoardSize boardSize_;
    std::chrono::year_month_day date_;
    std::chrono::seconds seconds_;

    explicit GameScore(const BoardSize &boardSize, const std::chrono::seconds &seconds)
        : boardSize_{boardSize}, date_{LocalDate::now()}, seconds_{seconds} {}

    explicit GameScore(const BoardSize &boardSize, const std::chrono::year_month_day &date, int seconds)
        : boardSize_{boardSize}, date_{date}, seconds_{seconds} {}

    bool operator==(const GameScore &) const = default;
    bool operator<(const GameScore &that) const { return this->seconds_ < that.seconds_; }
};
