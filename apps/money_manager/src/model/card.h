//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "cardtype.h"
#include "moneyrecord.h"
#include <QDate>

class Card final : public MoneyRecord {
  public:
    explicit Card(const QUuid &uuid, const QUuid accountUuid, const CardType &type, const QString &number,
                  QDate expiration, const QString &comment, bool enabled, long created, long modified);
    ~Card() = default;

    QUuid accountUuid() const noexcept { return accountUuid_; };
    const CardType &type() const noexcept { return CardType::valueOf(type_); }
    const QString &number() const noexcept { return number_; }
    QDate expiration() const noexcept { return expiration_; }
    const QString &comment() const noexcept { return comment_; }
    bool enabled() const noexcept { return enabled_; }

  private:
    QUuid accountUuid_;
    unsigned type_;
    QString number_;
    QDate expiration_;
    QString comment_;
    bool enabled_;
};
