//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "category.h"
#include <stdexcept>

Category::Category(const QUuid &uuid, const QString &name, const QString &comment, const CategoryType &type,
                   const std::optional<QUuid> &iconUuid, long created, long modified)
    : MoneyRecord{uuid, created, modified}, name_{name}, comment_{comment}, type_{type}, iconUuid_{iconUuid} {

    if (name.isEmpty()) {
        throw std::invalid_argument("name must not be empty");
    }
}
