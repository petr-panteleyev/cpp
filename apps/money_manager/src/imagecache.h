//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMAGECACHE_H
#define IMAGECACHE_H

class QImage;
class QUuid;

namespace ImageCache {

const QImage &getImage(const QUuid &uuid);

}

#endif // IMAGECACHE_H
