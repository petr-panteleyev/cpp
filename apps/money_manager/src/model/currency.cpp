//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "currency.h"
#include "decimal.h"

using Common::Decimal;

Currency::Currency(QUuid uuid, const QString &symbol, const QString &description, const QString &formatSymbol,
                   int formatSymbolPosition, bool showFormatSymbol, bool def, Decimal rate, int direction,
                   bool useThousandSeparator, long created, long modified)
    : MoneyRecord(uuid, created, modified), symbol_{symbol}, description_{description}, formatSymbol_{formatSymbol},
      formatSymbolPosition_{formatSymbolPosition}, showFormatSymbol_{showFormatSymbol}, def_{def}, rate_{rate},
      direction_{direction}, useThousandSeparator_{useThousandSeparator} {
}
