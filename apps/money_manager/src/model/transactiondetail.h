//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef TRANSACTIONDETAIL_H
#define TRANSACTIONDETAIL_H

#include "decimal.h"
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

#endif // TRANSACTIONDETAIL_H
