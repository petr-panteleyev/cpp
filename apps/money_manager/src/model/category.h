//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "categorytype.h"
#include "moneyrecord.h"
#include <QString>
#include <optional>

class Category final : public MoneyRecord {
  public:
    explicit Category(const QUuid &uuid, const QString &name, const QString &comment, const CategoryType &type,
                      const std::optional<QUuid> &iconUuid, long created, long modified);
    ~Category() = default;

    const QString &name() const noexcept { return name_; }
    const QString &comment() const noexcept { return comment_; }
    unsigned type() const noexcept { return type_; }
    const std::optional<QUuid> iconUuid() const noexcept { return iconUuid_; }

  private:
    QString name_;
    QString comment_;
    unsigned type_;
    std::optional<QUuid> iconUuid_;
};
