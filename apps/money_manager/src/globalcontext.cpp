//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "globalcontext.h"
#include "datacache.h"
#include "moneydao.h"

namespace GlobalContext {

static DataCache DATA_CACHE;
static MoneyDao MONEY_DAO{DATA_CACHE};

DataCache &cache() {
    return DATA_CACHE;
}

MoneyDao &dao() {
    return MONEY_DAO;
}

} // namespace GlobalContext
