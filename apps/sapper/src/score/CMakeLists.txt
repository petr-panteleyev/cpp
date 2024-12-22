# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(sapper PRIVATE
    scoreboard.h
    scoreboard.cpp
    scoreboarddialog.h
    scoreboarddialog.cpp
    scoreboarddialog.ui
    scoreboarditemmodel.h
    scoreboarditemmodel.cpp
)

target_include_directories(sapper PRIVATE .)
