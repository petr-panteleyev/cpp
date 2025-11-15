# Copyright © 2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(common VERSION 1.0.0 LANGUAGES CXX)

#
# Library
#

# add_library(common STATIC)

# target_compile_options(common PRIVATE -Werror -Wall -pedantic)

# target_sources(common
#     PUBLIC
#         src/localdate.hpp
#         src/numeric.hpp
#         src/enumclass.hpp
#         src/observablevalue.hpp
# )

# target_include_directories(common PRIVATE
#     ${CMAKE_SOURCE_DIR}/include
# )

#
# Tests
#

add_executable(common_tests)

find_package(GTest REQUIRED)

FILE(GLOB_RECURSE test_sources "test/*.cpp")
target_sources(common_tests PRIVATE ${test_sources})

target_include_directories(common_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    src
)

target_link_libraries(common_tests PRIVATE
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(common_tests)
