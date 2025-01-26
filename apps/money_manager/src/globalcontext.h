//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef GLOBALCONTEXT_H
#define GLOBALCONTEXT_H

class DataCache;
class MoneyDao;

namespace GlobalContext {

DataCache &cache();
MoneyDao &dao();

} // namespace GlobalContext

#endif // GLOBALCONTEXT_H
