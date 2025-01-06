//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "transaction.h"

using Common::Decimal;

Transaction::Transaction(QUuid uuid, Decimal amount, Decimal creditAmount, QDate transactionDate,
                         const TransactionType &type, const QString &comment, bool checked, QUuid accountDebitedUuid,
                         QUuid accountCreditedUuid, const CategoryType &accountDebitedType,
                         const CategoryType &accountCreditedType, QUuid accountDebitedCategoryUuid,
                         QUuid accountCreditedCategoryUuid, std::optional<QUuid> contactUuid,
                         const QString &invoiceNumber, std::optional<QUuid> parentUuid, bool detailed,
                         QDate statementDate, std::optional<QUuid> cardUuid, long created, long modified)
    : MoneyRecord(uuid, created, modified),

      amount_{amount}, creditAmount_{creditAmount}, transactionDate_{transactionDate}, type_{type}, comment_{comment},
      checked_{checked}, accountDebitedUuid_{accountDebitedUuid}, accountCreditedUuid_{accountCreditedUuid},
      accountDebitedType_{accountDebitedType}, accountCreditedType_{accountCreditedType},
      accountDebitedCategoryUuid_{accountDebitedCategoryUuid},
      accountCreditedCategoryUuid_{accountCreditedCategoryUuid}, contactUuid_{contactUuid},
      invoiceNumber_{invoiceNumber}, parentUuid_{parentUuid}, detailed_{detailed}, statementDate_{statementDate},
      cardUuid_{cardUuid} {
}
