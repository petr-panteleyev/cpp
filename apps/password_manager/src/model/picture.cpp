//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "picture.hpp"

static std::unordered_map<unsigned, QIcon> ICON_CACHE;

const QIcon &Picture::icon() const {
    auto result = ICON_CACHE.find(ordinal());
    return result != ICON_CACHE.end() ? result->second : ICON_CACHE[ordinal()] = QIcon(":images/" + fileName_);
}
