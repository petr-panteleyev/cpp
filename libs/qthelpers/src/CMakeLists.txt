# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

add_library(qthelpers STATIC)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_compile_options(qthelpers PRIVATE
    -Werror
    -Wall
    -pedantic
)

target_sources(qthelpers
    PUBLIC
        qthelpers.h
    PRIVATE
        qthelpers.cpp
)

target_link_libraries(qthelpers PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
