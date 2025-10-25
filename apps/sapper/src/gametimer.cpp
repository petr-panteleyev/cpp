//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "gametimer.h"
#include <QTimer>
#include <memory>

constexpr int INTERVAL_MS = 100;

GameTimer::GameTimer(GameTimerHandler &handler)
    : timer_{std::make_unique<QTimer>()}, localTime_{ZERO_TIME}, handler_{&handler} {
    QObject::connect(timer_.get(), &QTimer::timeout, [this]() { onTimer(); });
}

GameTimer::~GameTimer() {
}

void GameTimer::onTimer() {
    auto current = localTime_;
    localTime_ = localTime_.addMSecs(INTERVAL_MS);
    if (localTime_.second() != current.second()) {
        handler_->onTimerUpdate(localTime_);
    }
}

void GameTimer::start() {
    localTime_ = ZERO_TIME;
    timer_->start(INTERVAL_MS);
}

void GameTimer::stop() {
    timer_->stop();
}
