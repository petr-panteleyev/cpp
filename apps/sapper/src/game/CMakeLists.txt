# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(sapper PRIVATE
    boardsize.h
    game.h
    game.cpp
    board.h
    board.cpp
)

target_include_directories(sapper PRIVATE .)
