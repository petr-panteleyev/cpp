# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(sapper PRIVATE
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    buttoneventfilter.h
    buttoneventfilter.cpp
    pictures.h
    pictures.cpp
    gametimer.h
    gametimer.cpp
    boardsizedialog.h
    boardsizedialog.cpp
    boardsizedialog.ui
)

target_include_directories(sapper PRIVATE .)

add_subdirectory(game)
add_subdirectory(settings)
add_subdirectory(score)
