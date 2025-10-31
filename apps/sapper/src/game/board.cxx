//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include <algorithm>
#include <array>
#include <span>

export module apps.sapper.board;

import apps.sapper.boardsize;
import apps.sapper.cell;

export constexpr int AREA_SIZE = 9;
export using Area = std::array<int, AREA_SIZE>;

export struct MineCountResult {
    int value;
    Area neighbours;
};

export class Board final {
  public:
    explicit Board() noexcept : width_{0}, size_{0}, mines_{0}, remainingMines_{0} { board_.fill(0); };

    int size() const noexcept { return size_; }
    int remainingMines() const noexcept { return remainingMines_; }

    void setup(const BoardSize &size);

    void initialize(int center);

    int toggleFlag(int x);

    int value(int x) const noexcept { return board_[x]; }

    std::span<const int> const actualBoard() const {
        return std::span<const int>{board_.begin(), std::next(board_.begin(), size_)};
    }

    bool hasUnexploredCells() const noexcept { return hasUnexploredCells(actualBoard()); }
    void countRemainingMines() { remainingMines_ = mines_ - getFlagCount(actualBoard()); }

    MineCountResult countMines(int x) noexcept;

    static Area getUnopenedNeighbours(int center, int width, const std::span<const int> &board);

    static Area getCleanArea(int center, int width, int size);

    static bool hasUnexploredCells(const std::span<const int> &board) {
        return std::find_if(board.begin(), board.end(), [](int value) { return Cell::empty(value); }) != board.end();
    }

    static int getFlagCount(const std::span<const int> &board);

  private:
    static constexpr int MAX_MINES = 8;

  private:
    int width_;
    int size_;
    int mines_;
    int remainingMines_;

    std::array<int, BoardSize::BOARD_ARRAY_SIZE> board_;
};
