//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "board.h"
#include "cell.h"
#include <random>

static std::random_device rd;
static std::mt19937 randomGenerator(rd());

static int randomNumber(int max_value) {
    return randomGenerator() % max_value;
}

void Board::setup(const BoardSize &size) {
    width_ = size.width();
    size_ = width_ * size.height();
    mines_ = size.mines();
    remainingMines_ = mines_;
    board_.fill(Cell::EMPTY);
}

void Board::initialize(int center) {
    auto cleanArea = getCleanArea(center, width_, size_);

    for (auto i = 0; i < mines_;) {
        auto x = randomNumber(size_);
        if (std::find(cleanArea.begin(), cleanArea.end(), x) != cleanArea.end()) {
            continue;
        }
        if (board_[x] != Cell::EMPTY) {
            continue;
        }
        board_[x] = Cell::MINE;
        ++i;
    }
}

int Board::toggleFlag(int x) {
    auto value = board_[x];
    if (value <= MAX_MINES) {
        // Cannot toggle mine on opened cell, ignore
        return value;
    }
    value = Cell::toggleFlag(value);

    board_[x] = value;
    if (Cell::flag(value)) {
        --remainingMines_;
    } else {
        ++remainingMines_;
    }
    return value;
}

MineCountResult Board::countMines(int x) noexcept {
    auto neighbours = getUnopenedNeighbours(x, width_, actualBoard());
    auto mineCount = 0;
    for (auto neighbour : neighbours) {
        if (neighbour < 0) {
            break;
        }
        if (Cell::mine(value(neighbour))) {
            mineCount++;
        }
    }
    board_[x] = mineCount;
    return MineCountResult{mineCount, neighbours};
}

Area Board::getUnopenedNeighbours(int center, int width, const std::span<const int> &board) {
    Area result;
    result.fill(0);

    auto x = center % width;
    auto lowerAdd = x == 0 ? 0 : -1;
    auto upperAdd = x == width - 1 ? 0 : 1;

    auto index = 0;
    for (auto w = -width; w <= width; w += width) {
        for (int add = lowerAdd; add <= upperAdd; add += 1) {
            auto pos = center + w + add;
            if (pos == center || pos < 0 || pos >= static_cast<int>(board.size())) {
                continue;
            }

            if (board[pos] > MAX_MINES) {
                result[index++] = pos;
            }
        }
    }
    result[index] = -1;
    return result;
}

Area Board::getCleanArea(int center, int width, int size) {
    Area cleanArea;
    cleanArea.fill(std::numeric_limits<int>::max());

    auto x = center % width;
    auto lowerAdd = x == 0 ? 0 : -1;
    auto upperAdd = x == width - 1 ? 0 : 1;

    auto index = 0;
    for (auto w = -width; w <= width; w += width) {
        for (int add = lowerAdd; add <= upperAdd; add += 1) {
            auto pos = center + w + add;
            if (pos >= 0 && pos < size) {
                cleanArea[index++] = pos;
            }
        }
    }

    return cleanArea;
}

bool Board::hasUnexploredCells(const std::span<const int> &board) {
    return std::find_if(board.begin(), board.end(), [](int value) { return Cell::empty(value); }) != board.end();
}

int Board::getFlagCount(const std::span<const int> &board) {
    int result{0};

    for (auto value : board) {
        result += (value & Cell::FLAG_MASK);
    }

    return result >> 6;
}
