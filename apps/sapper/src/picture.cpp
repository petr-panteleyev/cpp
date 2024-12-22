/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "picture.h"
#include <unordered_map>

using std::cref;

const Picture Picture::ICON("ICON", "icon.png");
const Picture Picture::SMILING_FACE("SMILING_FACE", "smiling-face.png");
const Picture Picture::SAD_FACE("SAD_FACE", "sad-face.png");
const Picture Picture::LAUGHING_FACE("LAUGHING_FACE", "laughing-face.png");
const Picture Picture::RED_FLAG("RED_FLAG", "red-flag.png");
const Picture Picture::BLACK_FLAG("BLACK_FLAG", "black-flag.png");

template <>
const std::vector<PictureRef> Common::EnumClass<Picture>::values_{
    cref(Picture::ICON),          cref(Picture::SMILING_FACE), cref(Picture::SAD_FACE),
    cref(Picture::LAUGHING_FACE), cref(Picture::RED_FLAG),     cref(Picture::BLACK_FLAG),
};

static std::unordered_map<unsigned, QIcon> ICON_CACHE;

const QIcon &Picture::icon() const {
    auto result = ICON_CACHE.find(ordinal());
    return result != ICON_CACHE.end() ? result->second : ICON_CACHE[ordinal()] = QIcon(":images/" + fileName_);
}
