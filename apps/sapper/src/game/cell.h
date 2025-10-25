//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

namespace Cell {

constexpr int MAX_MINES = 8;

constexpr int EMPTY = 0b0010000;
constexpr int MINE = 0b0100000;
constexpr int FLAG_MASK = 0b1000000;

constexpr int EMPTY_WITH_FLAG = EMPTY | FLAG_MASK;
constexpr int MINE_WITH_FLAG = MINE | FLAG_MASK;

inline bool empty(int value) {
    return (value & EMPTY) == EMPTY;
}

inline bool emptyWithFlag(int value) {
    return value == EMPTY_WITH_FLAG;
}

inline bool mine(int value) {
    return (value & MINE) == MINE;
}

inline bool flag(int value) {
    return (value & FLAG_MASK) == FLAG_MASK;
}

inline bool mineNoFlag(int value) {
    return value == MINE;
}

inline int toggleFlag(int value) {
    return value ^ FLAG_MASK;
}

inline int putMine(int value) {
    return (value ^ MINE) & (~EMPTY);
}

inline bool isExplored(int value) {
    return value <= MAX_MINES;
}

} // namespace Cell
