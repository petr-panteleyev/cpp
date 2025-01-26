//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CURRENCY_H
#define CURRENCY_H

#include "decimal.h"
#include "moneyrecord.h"
#include <QString>
#include <QUuid>

class Currency final : public MoneyRecord {
  public:
    explicit Currency(QUuid uuid, const QString &symbol, const QString &description, const QString &formatSymbol,
                      int formatSymbolPosition, bool showFormatSymbol, bool def, Common::Decimal rate, int direction,
                      bool useThousandSeparator, long created, long modified);
    ~Currency() = default;

    const QString &symbol() const noexcept { return symbol_; }
    const QString &description() const noexcept { return description_; }

  private:
    const QString symbol_;
    const QString description_;
    const QString formatSymbol_;
    const int formatSymbolPosition_;
    const bool showFormatSymbol_;
    const bool def_;
    const Common::Decimal rate_;
    const int direction_;
    const bool useThousandSeparator_;
};

#endif // CURRENCY_H
