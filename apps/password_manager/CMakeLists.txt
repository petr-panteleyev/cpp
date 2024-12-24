# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

project(password_manager VERSION 24.12.4 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets LinguistTools Xml)
find_package(OpenSSL REQUIRED COMPONENTS Crypto)

qt_add_executable(password_manager)
add_subdirectory(src)

target_compile_options(password_manager PRIVATE
    -Werror
    -Wall
    -pedantic
)

file(GLOB PASSWORD_MANAGER_RESOURCE_FILES "resources/*.png")

target_compile_definitions(password_manager PRIVATE
    "PROJECT_VERSION=${PROJECT_VERSION}"
    "BUILD_TIMESTAMP=${BUILD_TIMESTAMP}"
)

qt_add_resources(password_manager "resources"
    PREFIX "/images"
    BASE "resources"
    FILES ${PASSWORD_MANAGER_RESOURCE_FILES}
)

qt_add_translations(password_manager
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
    TS_FILES
        src/ui/password_manager_ru_RU.ts
)

add_dependencies(password_manager password_manager_lupdate)

target_link_libraries(password_manager PRIVATE 
    Qt6::Core
    Qt6::Widgets
    Qt6::Xml
    OpenSSL::Crypto
    pwdgen
)

target_include_directories(password_manager PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/libs/pwdgen/src
)

set_target_properties(password_manager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS password_manager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
