# Copyright © 2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(qthelpers VERSION 1.0.0 LANGUAGES CXX)

add_library(qthelpers STATIC)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_compile_options(qthelpers PRIVATE -Werror -Wall -pedantic)

target_sources(qthelpers
    PUBLIC
    src/qthelpers.hpp
    PRIVATE
        src/qthelpers.cpp
)

target_link_libraries(qthelpers PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
