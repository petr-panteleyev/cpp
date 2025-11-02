//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module apps.sapper.gametimer;

import std;

namespace {

constexpr std::chrono::milliseconds ZERO_MS{0};
constexpr std::chrono::milliseconds INTERVAL_MS{100};

// Only one timer thread at a time is running
std::atomic_bool running{false};
std::mutex timerMutex;
std::chrono::milliseconds millis{0};

} // namespace

GameTimer::GameTimer(const std::function<void(std::chrono::seconds)> &handler) : handler_{handler} {
}

GameTimer::~GameTimer() {
    running = false;
}

void GameTimer::timerTask() {
    while (running) {
        std::this_thread::sleep_for(INTERVAL_MS);

        std::lock_guard<std::mutex> lock(timerMutex);
        millis += INTERVAL_MS;
        auto newSeconds = std::chrono::floor<std::chrono::seconds>(millis);

        if (newSeconds != this->seconds()) {
            seconds_.store(newSeconds);
            handler_(newSeconds);
        }
    }
}

void GameTimer::start() {
    if (running) return;

    std::lock_guard<std::mutex> lock(timerMutex);

    millis = ZERO_MS;

    running = true;
    std::thread timerThread{[this]() {
        timerTask();
    }};
    timerThread.detach();
}

void GameTimer::stop() {
    running = false;
}
