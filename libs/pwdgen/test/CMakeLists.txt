# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(pwdgen_tests)

find_package(GTest REQUIRED)

target_sources(pwdgen_tests PRIVATE
    pwdgentest.cpp
    characterset_test.cpp
)

target_include_directories(pwdgen_tests PRIVATE ../src)

target_link_libraries(pwdgen_tests PRIVATE
    pwdgen
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(pwdgen_tests)
