//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

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
    QString symbol_;
    QString description_;
    QString formatSymbol_;
    int formatSymbolPosition_;
    bool showFormatSymbol_;
    bool def_;
    Common::Decimal rate_;
    int direction_;
    bool useThousandSeparator_;
};
