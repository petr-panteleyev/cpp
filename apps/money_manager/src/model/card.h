//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARD_H
#define CARD_H

#include "cardtype.h"
#include "moneyrecord.h"
#include <QDate>

class Card final : public MoneyRecord {
  public:
    explicit Card(const QUuid &uuid, const QUuid accountUuid, const CardType &type, const QString &number,
                  QDate expiration, const QString &comment, bool enabled, long created, long modified);
    ~Card() = default;

    QUuid accountUuid() const noexcept { return accountUuid_; };
    const CardType &type() const noexcept { return type_; }
    const QString &number() const noexcept { return number_; }
    QDate expiration() const noexcept { return expiration_; }
    const QString &comment() const noexcept { return comment_; }
    bool enabled() const noexcept { return enabled_; }

  private:
    QUuid accountUuid_;
    const CardType &type_;
    QString number_;
    QDate expiration_;
    QString comment_;
    bool enabled_;
};

#endif // CARD_H
