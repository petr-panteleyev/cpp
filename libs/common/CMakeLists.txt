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
        FILE_SET CXX_MODULES
            TYPE CXX_MODULES
            FILES
                src/localdate.cxx
    PRIVATE
        src/decimal.cpp

        src/arithmeticexception.h
        src/decimal.h
        src/enumclass.h
        src/observablevalue.h
)

#
# Tests
#

add_executable(common_tests)

find_package(GTest REQUIRED)

FILE(GLOB_RECURSE test_sources "test/*.cpp")
target_sources(common_tests PRIVATE ${test_sources})

target_include_directories(common_tests PRIVATE src)

target_link_libraries(common_tests PRIVATE
    common
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(common_tests)
