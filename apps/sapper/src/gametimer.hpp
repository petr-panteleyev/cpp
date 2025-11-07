//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <atomic>
#include <chrono>
#include <functional>

class GameTimer final {
  private:
    static constexpr std::chrono::seconds ZERO_SEC{0};

  public:
    explicit GameTimer(const std::function<void(std::chrono::seconds)> &handler);
    ~GameTimer();

    void start();
    void stop();
    void reset() { handler_(ZERO_SEC); }

    std::chrono::seconds seconds() const { return seconds_; }

  private:
    GameTimer(const GameTimer &) = delete;
    GameTimer(const GameTimer &&) = delete;

    void timerTask();

  private:
    std::function<void(std::chrono::seconds)> handler_;
    std::atomic<std::chrono::seconds> seconds_;
};
