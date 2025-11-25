//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "resources.h"

// Fonts

static const unsigned char mineSweeperFontBytes[] = {
#embed "../resources/mine-sweeper.ttf"
};
const struct resource_t MINE_SWEEPER_FONT = {.bytes_ = mineSweeperFontBytes, .size_ = sizeof mineSweeperFontBytes};

static const unsigned char neatLcdFontBytes[] = {
#embed "../resources/neat-lcd.ttf"
};
const struct resource_t NEAT_LCD_FONT = {.bytes_ = neatLcdFontBytes, .size_ = sizeof neatLcdFontBytes};

// Icons

static const unsigned char blackFlagPngBytes[] = {
#embed "../resources/black-flag.png"
};
const struct resource_t BLACK_FLAG_PNG = {.bytes_ = blackFlagPngBytes, .size_ = sizeof blackFlagPngBytes};

static const unsigned char iconPngBytes[] = {
#embed "../resources/icon.png"
};
const struct resource_t ICON_PNG = {.bytes_ = iconPngBytes, .size_ = sizeof iconPngBytes};

static const unsigned char laughingFacePngBytes[] = {
#embed "../resources/laughing-face.png"
};
const struct resource_t LAUGHING_FACE_PNG = {.bytes_ = laughingFacePngBytes, .size_ = sizeof laughingFacePngBytes};

static const unsigned char redFlagPngBytes[] = {
#embed "../resources/red-flag.png"
};
const struct resource_t RED_FLAG_PNG = {.bytes_ = redFlagPngBytes, .size_ = sizeof redFlagPngBytes};

static const unsigned char sadFacePngBytes[] = {
#embed "../resources/sad-face.png"
};
const struct resource_t SAD_FACE_PNG = {.bytes_ = sadFacePngBytes, .size_ = sizeof sadFacePngBytes};

static const unsigned char smilingFacePngBytes[] = {
#embed "../resources/smiling-face.png"
};
const struct resource_t SMILING_FACE_PNG = {.bytes_ = smilingFacePngBytes, .size_ = sizeof smilingFacePngBytes};
