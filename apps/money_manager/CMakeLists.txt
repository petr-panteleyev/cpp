# Copyright © 2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(money_manager VERSION 25.1.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Xml Sql)

FILE(GLOB_RECURSE headers "src/*.h" "src/*.hpp")
FILE(GLOB_RECURSE sources "src/*.cpp" "src/*.ui")
qt_add_executable(money_manager ${headers} ${sources})

target_compile_options(money_manager PRIVATE -Werror -Wall -pedantic)

file(GLOB MONEY_MANAGER_RESOURCE_FILES "resources/*.png")

target_compile_definitions(money_manager PRIVATE
    "PROJECT_VERSION=${PROJECT_VERSION}"
    "BUILD_TIMESTAMP=${BUILD_TIMESTAMP}"
)

qt_add_resources(money_manager "resources"
    PREFIX "/images"
    BASE "resources"
    FILES ${MONEY_MANAGER_RESOURCE_FILES}
)

target_link_libraries(money_manager PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Sql
    common
    qthelpers
)

target_include_directories(money_manager PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/libs/common/src
  ${CMAKE_SOURCE_DIR}/libs/qthelpers/src
  src
  src/data
  src/database
  src/model
  src/persistence
  src/profiles
  src/settings
)

install(TARGETS money_manager
    RUNTIME DESTINATION money_manager
)

install(FILES
    resources/icon.png
    DESTINATION money_manager
)
