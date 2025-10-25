//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <vector>

class Card;
class ImportRecord;

namespace ImportUtil {

std::vector<ImportRecord> calculateImport(const std::vector<Card> &existing, const std::vector<Card> &toImport);

} // namespace ImportUtil
