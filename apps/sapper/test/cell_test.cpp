//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "cell.h"
#include <gtest/gtest.h>

void testMine(int value, bool expected) {
    EXPECT_EQ(Cell::mine(value), expected);
}

TEST(Sapper, Cell_mine) {
    testMine(0, false);
    testMine(8, false);
    testMine(0x20, true);
    testMine(0x30, true);
}

void testToggleFlag(int value, int expected) {
    EXPECT_EQ(Cell::toggleFlag(value), expected);
}

TEST(Sapper, Cell_toggleFlag) {
    testToggleFlag(Cell::EMPTY, Cell::EMPTY_WITH_FLAG);
    testToggleFlag(Cell::MINE, Cell::MINE_WITH_FLAG);
    testToggleFlag(Cell::EMPTY_WITH_FLAG, Cell::EMPTY);
    testToggleFlag(Cell::MINE_WITH_FLAG, Cell::MINE);
}

void testPutMine(int value, int expected) {
    EXPECT_EQ(Cell::putMine(value), expected);
}

TEST(Sapper, Cell_putMine) {
    testPutMine(Cell::EMPTY, Cell::MINE);
    testPutMine(Cell::EMPTY_WITH_FLAG, Cell::MINE_WITH_FLAG);
}
