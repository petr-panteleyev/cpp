//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

class QImage;
class QUuid;

namespace ImageCache {

const QImage &getImage(const QUuid &uuid);

}
