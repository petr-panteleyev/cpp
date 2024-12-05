/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "picture.h"

#include <functional>
#include <map>

using PictureRef = std::reference_wrapper<const Picture>;

const Picture Picture::FAVORITES{PictureEnum::FAVORITES, "FAVORITES", "favorites.png"};
const Picture Picture::GENERIC{PictureEnum::GENERIC, "GENERIC", "generic.png"};
const Picture Picture::MOBILE{PictureEnum::MOBILE, "MOBILE", "mobile.png"};
const Picture Picture::NOTE{PictureEnum::NOTE, "NOTE", "note.png"};
const Picture Picture::TRASH{PictureEnum::TRASH, "TRASH", "trash.png"};

static const std::vector<PictureRef> PICTURE_ENUM_VALUES = {
    std::cref(Picture::FAVORITES), std::cref(Picture::GENERIC), std::cref(Picture::MOBILE),
    std::cref(Picture::NOTE),      std::cref(Picture::TRASH),
};

static std::map<PictureEnum, QIcon> ICON_CACHE;

const Picture &Picture::valueOf(const std::string &name) {
    for (auto &entry : PICTURE_ENUM_VALUES) {
        if (entry.get().name() == name) {
            return entry;
        }
    }
    return Picture::GENERIC;
}

const QIcon &Picture::icon() const {
    auto result = ICON_CACHE.find(ordinal_);
    return result != ICON_CACHE.end() ? result->second : ICON_CACHE[ordinal_] = QIcon(":images/" + fileName_);
}
