//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "decimal.hpp"
#include <QString>
#include <QUuid>

class Transaction;

class TransactionDetail final {
  public:
    explicit TransactionDetail(QUuid uuid, Common::Decimal amount, QUuid accountCreditedUuid, const QString &comment,
                               long modified);

    explicit TransactionDetail(const Transaction &transaction);
    ~TransactionDetail() = default;

  private:
    QUuid uuid_;
    Common::Decimal amount_;
    QUuid accountCreditedUuid_;
    QString comment_;
    long modified_;
};
