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

#
# Tests
#

add_executable(qthelpers_tests)

find_package(GTest REQUIRED)

FILE(GLOB_RECURSE test_sources "test/*.cpp")
target_sources(qthelpers_tests PRIVATE
    ${test_sources}
    src/qthelpers.cpp
)

target_include_directories(qthelpers_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    src
)

target_link_libraries(qthelpers_tests PRIVATE
    ${GTEST_LIBRARIES}
    Qt${QT_VERSION_MAJOR}::Widgets
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(qthelpers_tests)
