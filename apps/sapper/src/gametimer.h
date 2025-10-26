//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QTime>
#include <chrono>

class QTimer;

class GameTimerHandler {
  public:
    virtual void onTimerUpdate(std::chrono::seconds seconds) = 0;
};

class GameTimer final {
  private:
    static inline const std::chrono::milliseconds ZERO_TIME{0};

  public:
    explicit GameTimer(GameTimerHandler &handler);
    ~GameTimer();

    void start();
    void stop();
    void reset() { handler_->onTimerUpdate(std::chrono::seconds{0}); }

    std::chrono::seconds seconds() const { return std::chrono::floor<std::chrono::seconds>(millis_); }

  private:
    GameTimer(const GameTimer &) = delete;
    GameTimer(const GameTimer &&) = delete;

    void onTimer();

  private:
    std::unique_ptr<QTimer> timer_;
    std::chrono::milliseconds millis_;
    GameTimerHandler *handler_;
};
