//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "card.h"

Card::Card(const QUuid &uuid, const QUuid accountUuid, const CardType &type, const QString &number, QDate expiration,
           const QString &comment, bool enabled, long created, long modified)
    : MoneyRecord{uuid, created, modified}, accountUuid_{accountUuid}, type_{type}, number_{number},
      expiration_{expiration}, comment_{comment}, enabled_{enabled} {
}
