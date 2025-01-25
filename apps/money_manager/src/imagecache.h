//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMAGECACHE_H
#define IMAGECACHE_H

#include <QImage>
#include <QUuid>
#include <memory>

namespace ImageCache {

std::shared_ptr<QImage> getImage(const QUuid &uuid);

}

#endif // IMAGECACHE_H
