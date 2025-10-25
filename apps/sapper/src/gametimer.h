//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QTime>

class QTimer;

class GameTimerHandler {
  public:
    virtual void onTimerUpdate(QTime time) = 0;
};

class GameTimer final {
  private:
    static inline const QTime ZERO_TIME{0, 0};

  public:
    explicit GameTimer(GameTimerHandler &handler);
    ~GameTimer();

    void start();
    void stop();
    void reset() { handler_->onTimerUpdate(ZERO_TIME); }

    QTime localTime() const noexcept { return localTime_; }

  private:
    GameTimer(const GameTimer &) = delete;
    GameTimer(const GameTimer &&) = delete;

    void onTimer();

  private:
    std::unique_ptr<QTimer> timer_;
    QTime localTime_;
    GameTimerHandler *handler_;
};
