# Copyright © 2024-2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(pwdgen VERSION 1.0.0 LANGUAGES CXX)

#
# Library
#

add_library(pwdgen STATIC)

target_compile_options(pwdgen PRIVATE -Werror -Wall -pedantic)

target_sources(pwdgen
    PUBLIC
        src/generator.h
    PRIVATE
        src/characterset.h
        src/characterset.cpp
        src/generator.cpp
)

#
# Tests
#

add_executable(pwdgen_tests)

find_package(GTest REQUIRED)

target_sources(pwdgen_tests PRIVATE
    test/pwdgentest.cpp
    test/characterset_test.cpp
)

target_include_directories(pwdgen_tests PRIVATE src)

target_link_libraries(pwdgen_tests PRIVATE
    pwdgen
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(pwdgen_tests)
