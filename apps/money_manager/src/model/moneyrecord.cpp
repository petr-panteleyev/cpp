//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "moneyrecord.h"
#include "timeutil.hpp"

MoneyRecord::MoneyRecord(QUuid uuid, long created, long modified) noexcept
    : uuid_{uuid}, created_{created}, modified_{modified} {

    long now = TimeUtil::currentTimeMillis();
    if (created == 0) {
        created_ = now;
    }
    if (modified == 0) {
        modified_ = 0;
    }
}
