# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(money_manager PRIVATE
    accountwindow.h
    accountwindow.cpp
    accountwindow.ui
    categorywindow.h
    categorywindow.cpp
    categorywindow.ui
    contactwindow.h
    contactwindow.cpp
    contactwindow.ui
    currencywindow.h
    currencywindow.cpp
    currencywindow.ui
    globalcontext.h
    globalcontext.cpp
    main.cpp
    mainwindow.h
    mainwindow.cpp
)

target_include_directories(money_manager PRIVATE .)

add_subdirectory(data)
add_subdirectory(model)
add_subdirectory(database)
add_subdirectory(persistence)
add_subdirectory(profiles)
