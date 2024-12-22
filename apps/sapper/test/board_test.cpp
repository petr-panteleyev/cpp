/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "board.h"
#include "cell.h"
#include <gtest/gtest.h>

static constexpr int MAX_VALUE = std::numeric_limits<int>::max();

static void testGetCleanArea(int center, int width, int size, const Area &expected) {
    EXPECT_EQ(Board::getCleanArea(center, width, size), expected);
}

TEST(Sapper, Board_getCleanArea) {
    Area e1{8, 9, 10, 15, 16, 17, 22, 23, 24};
    testGetCleanArea(16, 7, 35, e1);

    Area e2{0, 1, 7, 8, MAX_VALUE, MAX_VALUE, MAX_VALUE, MAX_VALUE, MAX_VALUE};
    testGetCleanArea(0, 7, 35, e2);

    Area e3{0, 1, 2, 7, 8, 9, MAX_VALUE, MAX_VALUE, MAX_VALUE};
    testGetCleanArea(1, 7, 35, e3);

    Area e4{5, 6, 12, 13, MAX_VALUE, MAX_VALUE, MAX_VALUE, MAX_VALUE, MAX_VALUE};
    testGetCleanArea(6, 7, 35, e4);

    Area e5{21, 22, 28, 29, MAX_VALUE, MAX_VALUE, MAX_VALUE, MAX_VALUE, MAX_VALUE};
    testGetCleanArea(28, 7, 35, e5);

    Area e6{21, 22, 23, 28, 29, 30, MAX_VALUE, MAX_VALUE, MAX_VALUE};
    testGetCleanArea(29, 7, 35, e6);

    Area e7{26, 27, 33, 34, MAX_VALUE, MAX_VALUE, MAX_VALUE, MAX_VALUE, MAX_VALUE};
    testGetCleanArea(34, 7, 35, e7);
}

static void testGetUnopenedNeighbours(int center, int width, const std::span<int> &board, const Area expected) {
    EXPECT_EQ(Board::getUnopenedNeighbours(center, width, board), expected);
}

TEST(Sapper, Board_getUnopenedNeighbours) {
    std::array<int, 20> b1{
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::MINE,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
    };
    Area e1{1, 5, 6, -1, 0, 0, 0, 0, 0};
    testGetUnopenedNeighbours(0, 5, b1, e1);

    std::array<int, 20> b2{
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, 2,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
    };
    Area e2{1, 5, -1, 0, 0, 0, 0, 0, 0};
    testGetUnopenedNeighbours(0, 5, b2, e2);

    std::array<int, 20> b3{
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, 2,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
    };
    Area e3{0, 2, 5, 7, -1, 0, 0, 0, 0};
    testGetUnopenedNeighbours(1, 5, b3, e3);

    std::array<int, 20> b4{
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
    };
    Area e4{0, 1, 2, 5, 7, 10, 11, 12, -1};
    testGetUnopenedNeighbours(6, 5, b4, e4);

    std::array<int, 20> b5{
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
        Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
    };
    Area e5{10, 11, 16, -1, 0, 0, 0, 0, 0};
    testGetUnopenedNeighbours(15, 5, b5, e5);
}

static void testHasUnexploredCells(const std::span<int> &board, int size, bool expected) {
    auto subBoard = std::span<const int>(board.begin(), std::next(board.begin(), size));
    EXPECT_EQ(Board::hasUnexploredCells(subBoard), expected);
}

TEST(Sapper, Board_hasUnexploredCells) {
    std::array<int, 4> a1{Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::EMPTY};
    testHasUnexploredCells(a1, 3, true);

    std::array<int, 4> a2{Cell::MINE, Cell::MINE, Cell::MINE, Cell::EMPTY};
    testHasUnexploredCells(a2, 3, false);

    std::array<int, 4> a3{Cell::MINE, Cell::MINE, Cell::EMPTY_WITH_FLAG, Cell::EMPTY};
    testHasUnexploredCells(a3, 3, true);

    std::array<int, 4> a4{Cell::MINE, Cell::MINE, 3, Cell::EMPTY};
    testHasUnexploredCells(a4, 3, false);
}

static void testGetFlagCount(const std::span<int> &board, int size, int expected) {
    auto subBoard = std::span<const int>(board.begin(), std::next(board.begin(), size));
    EXPECT_EQ(Board::getFlagCount(subBoard), expected);
}

TEST(Sapper, Board_getFlagCount) {
    std::array<int, 4> a1{Cell::EMPTY, Cell::EMPTY, Cell::EMPTY, Cell::MINE_WITH_FLAG};
    testGetFlagCount(a1, 3, 0);

    std::array<int, 4> a2{Cell::EMPTY, Cell::EMPTY, Cell::MINE_WITH_FLAG, Cell::MINE_WITH_FLAG};
    testGetFlagCount(a2, 3, 1);

    std::array<int, 4> a3{Cell::MINE_WITH_FLAG, Cell::EMPTY, Cell::EMPTY_WITH_FLAG, Cell::MINE_WITH_FLAG};
    testGetFlagCount(a3, 3, 2);

    std::array<int, 4> a4{Cell::MINE_WITH_FLAG, 2, Cell::EMPTY_WITH_FLAG, Cell::MINE_WITH_FLAG};
    testGetFlagCount(a4, 3, 2);
}
