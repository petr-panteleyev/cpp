# Copyright © 2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(common VERSION 1.0.0 LANGUAGES CXX)

#
# Library
#

add_library(common STATIC)

target_compile_options(common PRIVATE -Werror -Wall -pedantic)

target_sources(common
    PUBLIC
        src/arithmeticexception.h
        src/decimal.h
        src/enumclass.h
        src/observablevalue.h
    PRIVATE
        src/decimal.cpp
)

#
# Tests
#

add_executable(common_tests)

find_package(GTest REQUIRED)

target_sources(common_tests PRIVATE
    test/decimaltest.cpp
)

target_include_directories(common_tests PRIVATE src)

target_link_libraries(common_tests PRIVATE
    common
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(common_tests)
