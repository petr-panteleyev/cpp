/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef PICTURES_H
#define PICTURES_H

enum class Picture {
    ICON,
    SMILING_FACE,
    SAD_FACE,
    LAUGHING_FACE,
    RED_FLAG,
    BLACK_FLAG,
};

class QIcon;

namespace Pictures {
QIcon &icon(Picture picture);
}

#endif // PICTURE_H
