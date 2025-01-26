//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "imagecache.h"
#include "datacache.h"
#include "icon.h"
#include <QHash>
#include <stdexcept>

namespace ImageCache {

static QHash<QUuid, std::shared_ptr<QImage>> IMAGES;

std::shared_ptr<QImage> getImage(const QUuid &uuid) {
    if (IMAGES.contains(uuid)) {
        return IMAGES[uuid];
    }

    auto icon = DataCache::cache().getIcon(uuid);
    if (!icon.has_value()) {
        throw std::out_of_range("Icon does not exist");
    }

    auto image = std::make_shared<QImage>();
    image->loadFromData(icon.value()->bytes());
    IMAGES[uuid] = image;
    return image;
}

} // namespace ImageCache
