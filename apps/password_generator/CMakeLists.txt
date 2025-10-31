# Copyright © 2024-2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(password_generator VERSION 25.10.2 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC ON)

set(PASSWORD_GENERATOR_RESOURCE_FILES
    resources/icon.png
)

qt_add_executable(password_generator)
target_sources(password_generator
    PUBLIC
        FILE_SET CXX_MODULES
            TYPE CXX_MODULES
            FILES
                src/password_generator.cxx
                src/util.cxx
    PRIVATE
        src/main.cpp
        src/password_generator.cpp
        src/mainwindow.ui
)

target_compile_options(password_generator PRIVATE -Werror -Wall -pedantic)

qt_add_resources(password_generator "resources"
    PREFIX "/images"
    BASE "resources"
    FILES ${PASSWORD_GENERATOR_RESOURCE_FILES}
)

target_link_libraries(password_generator PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    pwdgen
)

target_include_directories(password_generator PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/pwdgen/src
)

install(TARGETS password_generator
    RUNTIME DESTINATION password_generator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install (FILES
    resources/icon.png
    DESTINATION password_generator
)
