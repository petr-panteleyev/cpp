/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "picture.h"
#include <unordered_map>

static std::unordered_map<unsigned, QIcon> ICON_CACHE;

const QIcon &Picture::icon() const {
    auto result = ICON_CACHE.find(ordinal());
    return result != ICON_CACHE.end() ? result->second : ICON_CACHE[ordinal()] = QIcon(":images/" + fileName_);
}
