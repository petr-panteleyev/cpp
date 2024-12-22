# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

project(password_generator VERSION 24.11.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PASSWORD_GENERATOR_RESOURCE_FILES
    resources/icon.png
)

qt_add_executable(password_generator)
add_subdirectory(src)

target_compile_options(password_generator PRIVATE
    -Werror
    -Wall
    -pedantic
)

qt_add_resources(password_generator "resources"
    PREFIX "/images"
    BASE "resources"
    FILES ${PASSWORD_GENERATOR_RESOURCE_FILES}
)

qt_add_translations(password_generator
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TS_FILES
        src/password_generator_ru.ts
)

add_dependencies(password_generator password_generator_lupdate)

target_link_libraries(password_generator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets pwdgen)

target_include_directories(password_generator PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/pwdgen/src
)

set_target_properties(password_generator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS password_generator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
