//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef MONEYRECORD_H
#define MONEYRECORD_H

#include <QUuid>

class MoneyRecord {
  public:
    explicit MoneyRecord(QUuid uuid, long created, long modified) noexcept;
    virtual ~MoneyRecord() = default;

    QUuid uuid() const noexcept { return uuid_; }
    long created() const noexcept { return created_; }
    long modified() const noexcept { return modified_; }

  private:
    QUuid uuid_;
    long created_;
    long modified_;
};

#endif // MONEYRECORD_H
