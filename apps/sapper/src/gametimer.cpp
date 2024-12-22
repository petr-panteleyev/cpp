/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "gametimer.h"

constexpr int INTERVAL_MS = 100;

GameTimer::GameTimer() : timer_{this}, localTime_{0, 0} {
    connect(&timer_, &QTimer::timeout, this, &GameTimer::onTimer);
}

void GameTimer::onTimer() {
    auto current = localTime_;
    localTime_ = localTime_.addMSecs(INTERVAL_MS);
    if (localTime_ != current) {
        emit timeString(localTime_.toString("mm:ss.z"));
    }
}

void GameTimer::start() {
    localTime_ = QTime{0, 0};
    timer_.start(INTERVAL_MS);
}
