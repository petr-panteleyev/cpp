//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "categorytype.h"
#include "decimal.h"
#include "moneyrecord.h"
#include "transactiontype.h"
#include <QDate>
#include <QUuid>
#include <optional>

class Transaction final : public MoneyRecord {
  public:
    Transaction(QUuid uuid, Common::Decimal amount, Common::Decimal creditAmount, QDate transactionDate,
                const TransactionType &type, const QString &comment, bool checked_, QUuid accountDebitedUuid,
                QUuid accountCreditedUuid, const CategoryType &accountDebitedType,
                const CategoryType &accountCreditedType, QUuid accountDebitedCategoryUuid,
                QUuid accountCreditedCategoryUuid, std::optional<QUuid> contactUuid, const QString &invoiceNumber,
                std::optional<QUuid> parentUuid, bool detailed, QDate statementDate, std::optional<QUuid> cardUuid,
                long created, long modified);
    ~Transaction() = default;

    Common::Decimal amount() const noexcept { return amount_; }
    QDate transactionDate() const noexcept { return transactionDate_; }
    const TransactionType &type() const noexcept { return type_; }
    const QString &comment() const noexcept { return comment_; }
    bool checked() const noexcept { return checked_; }
    QUuid accountDebitedUuid() const noexcept { return accountDebitedUuid_; }
    QUuid accountCreditedUuid() const noexcept { return accountCreditedUuid_; }
    const CategoryType &accountDebitedType() const noexcept { return accountDebitedType_; }
    const CategoryType &accountCreditedType() const noexcept { return accountCreditedType_; }
    std::optional<QUuid> contactUuid() const noexcept { return contactUuid_; }

  private:
    Common::Decimal amount_;
    Common::Decimal creditAmount_;
    QDate transactionDate_;
    const TransactionType &type_;
    QString comment_;
    bool checked_;
    QUuid accountDebitedUuid_;
    QUuid accountCreditedUuid_;
    const CategoryType &accountDebitedType_;
    const CategoryType &accountCreditedType_;
    QUuid accountDebitedCategoryUuid_;
    QUuid accountCreditedCategoryUuid_;
    std::optional<QUuid> contactUuid_;
    QString invoiceNumber_;
    std::optional<QUuid> parentUuid_;
    bool detailed_;
    QDate statementDate_;
    std::optional<QUuid> cardUuid_;
};

#endif // TRANSACTION_H
