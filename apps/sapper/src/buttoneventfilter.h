//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef BUTTONEVENTFILTER_H
#define BUTTONEVENTFILTER_H

#include <QObject>

class ButtonEventFilter final : public QObject {
  public:
    explicit ButtonEventFilter(QObject *parent) : QObject{parent}, disabled_{false} {};

    void setDisabled(bool disabled) noexcept { disabled_ = disabled; }

  protected:
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

  private:
    bool disabled_;
};

#endif // BUTTONEVENTFILTER_H
