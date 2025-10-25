//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "categorytype.h"
#include "decimal.h"
#include "moneyrecord.h"
#include <QDate>
#include <QString>
#include <QUuid>
#include <optional>

class Account final : public MoneyRecord {
  public:
    explicit Account(QUuid uuid, const QString &name, const QString &comment, const QString &accountNumber,
                     Common::Decimal openingBalance, Common::Decimal accountLimit, Common::Decimal currencyRate,
                     const CategoryType &type, QUuid categoryUuid, std::optional<QUuid> currencyUuid,
                     std::optional<QUuid> securityUuid, bool enabled, Common::Decimal interest,
                     std::optional<QDate> closingDate, std::optional<QUuid> iconUuid, Common::Decimal total,
                     Common::Decimal totalWaiting, long created, long modified);
    ~Account() = default;

    const QString &name() const noexcept { return name_; }
    const QString &comment() const noexcept { return comment_; }
    unsigned type() const noexcept { return type_; }
    QUuid categoryUuid() const noexcept { return categoryUuid_; }
    std::optional<QUuid> currencyUuid() const noexcept { return currencyUuid_; }
    Common::Decimal interest() const noexcept { return interest_; }
    std::optional<QDate> closingDate() const noexcept { return closingDate_; }
    std::optional<QUuid> iconUuid() const noexcept { return iconUuid_; }
    Common::Decimal total() const noexcept { return total_; }
    Common::Decimal totalWaiting() const noexcept { return totalWaiting_; }

  private:
    QString name_;
    QString comment_;
    QString accountNumber_;
    Common::Decimal openingBalance_;
    Common::Decimal accountLimit_;
    Common::Decimal currencyRate_;
    unsigned type_;
    QUuid categoryUuid_;
    std::optional<QUuid> currencyUuid_;
    std::optional<QUuid> securityUuid_;
    bool enabled_;
    Common::Decimal interest_;
    std::optional<QDate> closingDate_;
    std::optional<QUuid> iconUuid_;
    Common::Decimal total_;
    Common::Decimal totalWaiting_;
};
