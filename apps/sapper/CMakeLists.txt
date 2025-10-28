# Copyright © 2024-2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(sapper VERSION 25.10.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(GTest REQUIRED)

#
# Executable
#

FILE(GLOB_RECURSE headers "src/*.h" "src/*.hpp")
FILE(GLOB_RECURSE sources "src/*.cpp" "src/*.ui")
qt_add_executable(sapper ${headers} ${sources})
target_sources(sapper
    PUBLIC
        FILE_SET CXX_MODULES
            TYPE CXX_MODULES
            FILES
                src/game/cell.cxx
)

target_compile_options(sapper PRIVATE -Werror -Wall -pedantic)

file(GLOB SAPPER_RESOURCE_FILES "resources/*.png")

target_compile_definitions(sapper PRIVATE
    "PROJECT_VERSION=${PROJECT_VERSION}"
    "BUILD_TIMESTAMP=${BUILD_TIMESTAMP}"
)

qt_add_resources(sapper "resources"
    PREFIX "/images"
    BASE "resources"
    FILES ${SAPPER_RESOURCE_FILES}
)

qt_add_resources(sapper "fonts"
    PREFIX "/fonts"
    BASE "resources"
    FILES
        resources/mine-sweeper.ttf
        resources/neat-lcd.ttf
)

target_link_libraries(sapper PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    common
)

target_include_directories(sapper PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/libs/common/src
  src/game
  src/score
  src/settings
)

install(TARGETS sapper
    RUNTIME DESTINATION sapper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install (FILES
    resources/icon.png
    DESTINATION sapper
)

#
# Tests
#

add_executable(sapper_tests)

FILE(GLOB_RECURSE test_sources "test/*.cpp")

target_sources(sapper_tests PRIVATE
    ${test_sources}
    src/game/board.cpp
)
target_sources(sapper_tests
    PUBLIC
        FILE_SET CXX_MODULES
            TYPE CXX_MODULES
            FILES
                src/game/cell.cxx
)

target_include_directories(sapper_tests PRIVATE
    src
    src/game
)

target_link_libraries(sapper_tests PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(sapper_tests)

