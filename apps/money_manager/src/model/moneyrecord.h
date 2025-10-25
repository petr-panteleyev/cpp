//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

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
