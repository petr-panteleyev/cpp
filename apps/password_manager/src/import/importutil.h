//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMPORTUTIL_H
#define IMPORTUTIL_H

#include "importrecord.h"

namespace ImportUtil {

ImportRecordVec calculateImport(const std::vector<std::shared_ptr<Card>> &existing,
                                const std::vector<std::shared_ptr<Card>> &toImport);

} // namespace ImportUtil

#endif // IMPORTUTIL_H
