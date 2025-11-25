//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "pictures.hpp"
#include "resources.h"
#include <QIcon>

namespace {

const std::unordered_map<Picture, const struct res::resource_t *> RESOURCES{
    {Picture::ICON, &res::ICON_PNG},         {Picture::SMILING_FACE, &res::SMILING_FACE_PNG},
    {Picture::SAD_FACE, &res::SAD_FACE_PNG}, {Picture::LAUGHING_FACE, &res::LAUGHING_FACE_PNG},
    {Picture::RED_FLAG, &res::RED_FLAG_PNG}, {Picture::BLACK_FLAG, &res::BLACK_FLAG_PNG},
};

std::unordered_map<Picture, QIcon> ICON_CACHE;

} // namespace

namespace Pictures {

const QIcon &icon(Picture picture) {
    auto result = ICON_CACHE.find(picture);
    if (result != ICON_CACHE.end()) {
        return result->second;
    }

    const auto imageData = RESOURCES.at(picture);
    return ICON_CACHE[picture] = QIcon(QPixmap::fromImage(
               QImage::fromData(QByteArray(reinterpret_cast<const char *>(imageData->bytes_), imageData->size_))));
}

} // namespace Pictures
