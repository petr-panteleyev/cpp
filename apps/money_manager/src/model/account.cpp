//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "account.h"
#include <stdexcept>

using Common::Decimal;

Account::Account(QUuid uuid, const QString &name, const QString &comment, const QString &accountNumber,
                 Decimal openingBalance, Decimal accountLimit, Decimal currencyRate, const CategoryType &type,
                 QUuid categoryUuid, std::optional<QUuid> currencyUuid, std::optional<QUuid> securityUuid, bool enabled,
                 Decimal interest, std::optional<QDate> closingDate, std::optional<QUuid> iconUuid, Decimal total,
                 Decimal totalWaiting, long created, long modified)
    : MoneyRecord{uuid, created, modified}, name_{name}, comment_{comment}, accountNumber_{accountNumber},
      openingBalance_{openingBalance}, accountLimit_{accountLimit}, currencyRate_{currencyRate}, type_{type.ordinal()},
      categoryUuid_{categoryUuid}, currencyUuid_{currencyUuid}, securityUuid_{securityUuid}, enabled_{enabled},
      interest_{interest}, closingDate_{closingDate}, iconUuid_{iconUuid}, total_{total}, totalWaiting_{totalWaiting} {

    if (name.isEmpty()) {
        throw std::invalid_argument("Account name cannot be empty");
    }
}
