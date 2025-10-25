/*
  Copyright © 2024-2025 Petr Panteleyev
  SPDX-License-Identifier: BSD-2-Clause
*/

#pragma once

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
