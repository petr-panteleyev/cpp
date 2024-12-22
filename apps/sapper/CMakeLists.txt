# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

project(sapper VERSION 24.12.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_add_executable(sapper)
add_subdirectory(src)
add_subdirectory(test)

target_compile_options(sapper PRIVATE
    -Werror
    -Wall
    -pedantic
)

file(GLOB SAPPER_RESOURCE_FILES "resources/*.png")

target_compile_definitions(sapper
                           PRIVATE "PROJECT_VERSION=${PROJECT_VERSION}")

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

qt_add_translations(sapper
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TS_FILES
        src/sapper_ru_RU.ts
)

add_dependencies(sapper sapper_lupdate)

target_link_libraries(sapper PRIVATE
    Qt6::Core
    Qt6::Widgets
)

target_include_directories(sapper PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(sapper PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS sapper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
