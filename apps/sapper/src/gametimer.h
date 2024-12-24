//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef GAMETIMER_H
#define GAMETIMER_H

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

#endif // GAMETIMER_H
