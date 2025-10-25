//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

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
