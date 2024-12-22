# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(sapper_tests)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(GTest REQUIRED)

target_sources(sapper_tests PRIVATE
    board_test.cpp
    cell_test.cpp
    ../src/game/board.cpp
)

target_include_directories(sapper_tests PRIVATE
    ../src
    ../src/game
)

target_link_libraries(sapper_tests PRIVATE
    Qt6::Core
    Qt6::Widgets
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(sapper_tests)

