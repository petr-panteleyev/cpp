/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef GAMETIMER_H
#define GAMETIMER_H

#include "qdatetime.h"
#include "qtmetamacros.h"
#include <QTimer>

class GameTimer : public QObject {
    Q_OBJECT

  public:
    explicit GameTimer();

    void start();
    void stop() { timer_.stop(); };
    void reset() { emit timeString("00:00"); }

    QTime localTime() const noexcept { return localTime_; }

  signals:
    void timeString(const QString &text) const;

  private:
    void onTimer();

  private:
    QTimer timer_;
    QTime  localTime_;
};

#endif // GAMETIMER_H
