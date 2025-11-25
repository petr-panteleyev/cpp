//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#ifdef __cplusplus
namespace res {
extern "C" {
#endif

struct resource_t {
    const unsigned char *bytes_;
    unsigned long size_;
};

// Fonts
extern const struct resource_t MINE_SWEEPER_FONT;
extern const struct resource_t NEAT_LCD_FONT;

// Images
extern const struct resource_t BLACK_FLAG_PNG;
extern const struct resource_t ICON_PNG;
extern const struct resource_t LAUGHING_FACE_PNG;
extern const struct resource_t RED_FLAG_PNG;
extern const struct resource_t SAD_FACE_PNG;
extern const struct resource_t SMILING_FACE_PNG;

#ifdef __cplusplus
}
}
#endif
