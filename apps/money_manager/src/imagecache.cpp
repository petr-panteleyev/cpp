//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "imagecache.h"
#include "datacache.h"
#include "icon.h"
#include <QImage>
#include <QUuid>
#include <algorithm>
#include <memory>
#include <vector>

namespace ImageCache {

static std::vector<std::pair<QUuid, std::unique_ptr<QImage>>> IMAGES;

const QImage &getImage(const QUuid &uuid) {
    auto found = std::find_if(IMAGES.begin(), IMAGES.end(), [&uuid](const auto &pair) { return pair.first == uuid; });
    if (found != IMAGES.end()) {
        return *found->second;
    }

    auto icon = DataCache::cache().getIcon(uuid);
    auto image = new QImage();
    image->loadFromData(icon.bytes());
    IMAGES.emplace_back(uuid, std::unique_ptr<QImage>(image));

    return *image;
}

} // namespace ImageCache
