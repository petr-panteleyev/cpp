//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef ICON_H
#define ICON_H

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

#endif // ICON_H
