/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "pictures.h"
#include <QIcon>

static std::unordered_map<Picture, QString> FILE_NAMES{
    {Picture::ICON, "icon.png"},         {Picture::SMILING_FACE, "smiling-face.png"},
    {Picture::SAD_FACE, "sad-face.png"}, {Picture::LAUGHING_FACE, "laughing-face.png"},
    {Picture::RED_FLAG, "red-flag.png"}, {Picture::BLACK_FLAG, "black-flag.png"},
};

static std::unordered_map<Picture, QIcon> ICON_CACHE;

namespace Pictures {

QIcon &icon(Picture picture) {
    auto result = ICON_CACHE.find(picture);
    if (result != ICON_CACHE.end()) {
        return result->second;
    }
    return ICON_CACHE[picture] = QIcon(":images/" + FILE_NAMES.at(picture));
}

} // namespace Pictures
