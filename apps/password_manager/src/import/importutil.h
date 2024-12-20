/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef IMPORTUTIL_H
#define IMPORTUTIL_H

#include "card.h"
#include "importrecord.h"

namespace ImportUtil {

ImportRecordVec calculateImport(const CardVec &existing, const CardVec &toImport);

} // namespace ImportUtil

#endif // IMPORTUTIL_H
