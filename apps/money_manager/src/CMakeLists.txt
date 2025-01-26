# Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(money_manager PRIVATE
    accountwindow.h
    accountwindow.cpp
    accountwindow.ui
    cardwindow.h
    cardwindow.cpp
    cardwindow.ui
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
    imagecache.h
    imagecache.cpp
    main.cpp
    mainwindow.h
    mainwindow.cpp
    translation.h
    translation.cpp
)

target_include_directories(money_manager PRIVATE .)

add_subdirectory(data)
add_subdirectory(model)
add_subdirectory(database)
add_subdirectory(persistence)
add_subdirectory(profiles)
add_subdirectory(settings)
