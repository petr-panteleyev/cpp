//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "transactiondetail.h"
#include "transaction.h"

using Numeric::Decimal;

TransactionDetail::TransactionDetail(QUuid uuid, Decimal amount, QUuid accountCreditedUuid, const QString &comment,
                                     long modified)
    : uuid_{uuid}, amount_{amount}, accountCreditedUuid_{accountCreditedUuid}, comment_{comment}, modified_{modified} {
}

TransactionDetail::TransactionDetail(const Transaction &transaction)
    : uuid_{transaction.uuid()}, amount_{transaction.amount()}, accountCreditedUuid_{transaction.accountCreditedUuid()},
      comment_{transaction.comment()}, modified_{transaction.modified()} {
}
