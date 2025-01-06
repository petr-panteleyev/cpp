//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef ICON_H
#define ICON_H

#include "moneyrecord.h"
#include <QString>

class Icon final : public MoneyRecord {
  public:
    explicit Icon(QUuid uuid, const QString &name, const std::vector<std::byte> &bytes, long created, long modified);
    ~Icon() = default;

  private:
    QString name_;
    std::vector<std::byte> bytes_;
};

#endif // ICON_H
