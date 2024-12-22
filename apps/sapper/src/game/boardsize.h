/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef BOARDSIZE_H
#define BOARDSIZE_H

#include <QString>
#include <functional>
#include <stdexcept>
#include <vector>

class BoardSize final {
  public:
    static constexpr int MIN_WIDTH{8};
    static constexpr int MAX_WIDTH{30};
    static constexpr int MIN_HEIGHT{8};
    static constexpr int MAX_HEIGHT{24};
    static constexpr int BOARD_ARRAY_SIZE = MAX_HEIGHT * MAX_WIDTH;

    static const BoardSize                                            BIG, MEDIUM, SMALL;
    static const std::vector<std::reference_wrapper<const BoardSize>> STANDARD_SIZES;

  public:
    int width() const noexcept { return width_; }
    int height() const noexcept { return height_; }
    int mines() const noexcept { return mines_; }

    QString toString() const { return QString("%1 * %2 : %3").arg(width_).arg(height_).arg(mines_); }

    static BoardSize boardSize(int width, int height, int mines) {
        if (width < MIN_WIDTH || width > MAX_WIDTH || height < MIN_HEIGHT || height > MAX_HEIGHT) {
            throw std::out_of_range("Board dimensions are out of bounds");
        }
        return BoardSize(width, height, mines);
    }

  private:
    explicit BoardSize(int width, int height, int mines) noexcept : width_{width}, height_{height}, mines_{mines} {};

  private:
    int width_;
    int height_;
    int mines_;
};

inline const BoardSize BoardSize::BIG{30, 16, 99};
inline const BoardSize BoardSize::MEDIUM{16, 16, 40};
inline const BoardSize BoardSize::SMALL{8, 8, 10};

inline const std::vector<std::reference_wrapper<const BoardSize>> BoardSize::STANDARD_SIZES{
    std::cref(BoardSize::BIG),
    std::cref(BoardSize::MEDIUM),
    std::cref(BoardSize::SMALL),
};



#endif // BOARDSIZE_H
