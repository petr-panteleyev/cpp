//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "gametimer.h"
#include <QTimer>
#include <memory>

namespace {

constexpr int INTERVAL_MS = 100;

} // namespace

GameTimer::GameTimer(GameTimerHandler &handler)
    : timer_{std::make_unique<QTimer>()}, millis_{ZERO_TIME}, handler_{&handler} {
    QObject::connect(timer_.get(), &QTimer::timeout, [this]() { onTimer(); });
}

GameTimer::~GameTimer() {
}

void GameTimer::onTimer() {
    auto currentSeconds = seconds();
    millis_ += std::chrono::milliseconds{INTERVAL_MS};
    auto newSeconds = seconds();
    if (newSeconds != currentSeconds) {
        handler_->onTimerUpdate(newSeconds);
    }
}

void GameTimer::start() {
    millis_ = ZERO_TIME;
    timer_->start(INTERVAL_MS);
}

void GameTimer::stop() {
    timer_->stop();
}
