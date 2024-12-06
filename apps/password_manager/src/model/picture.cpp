/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "picture.h"
#include <map>

static std::map<unsigned, QIcon> ICON_CACHE;

const Picture &Picture::valueOf(const std::string &name) {
    for (const Picture &picture : values_) {
        if (picture.name() == name) {
            return picture;
        }
    }
    return Picture::GENERIC;
}

const QIcon &Picture::icon() const {
    auto result = ICON_CACHE.find(ordinal_);
    return result != ICON_CACHE.end() ? result->second : ICON_CACHE[ordinal_] = QIcon(":images/" + fileName_);
}
