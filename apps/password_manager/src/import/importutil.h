//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMPORTUTIL_H
#define IMPORTUTIL_H

#include <vector>

class Card;
class ImportRecord;

namespace ImportUtil {

std::vector<ImportRecord> calculateImport(const std::vector<Card> &existing, const std::vector<Card> &toImport);

} // namespace ImportUtil

#endif // IMPORTUTIL_H
