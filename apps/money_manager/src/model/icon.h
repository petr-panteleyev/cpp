//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "moneyrecord.h"
#include <QByteArray>
#include <QString>

class Icon final : public MoneyRecord {
  public:
    explicit Icon(QUuid uuid, const QString &name, const QByteArray &bytes, long created, long modified);
    ~Icon() = default;

    const QString &name() const noexcept { return name_; }
    const QByteArray &bytes() const noexcept { return bytes_; }

  private:
    QString name_;
    QByteArray bytes_;
};
