# Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(common_tests)

find_package(GTest REQUIRED)

target_sources(common_tests PRIVATE
    decimaltest.cpp
)

target_include_directories(common_tests PRIVATE ../src)

target_link_libraries(common_tests PRIVATE
    common
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(common_tests)
