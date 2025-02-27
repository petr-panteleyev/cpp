# Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

project(password_manager VERSION 25.2.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Xml)
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

target_link_libraries(password_manager PRIVATE 
    Qt6::Core
    Qt6::Widgets
    Qt6::Xml
    OpenSSL::Crypto
    pwdgen
    qthelpers
)

target_include_directories(password_manager PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/pwdgen/src
    ${CMAKE_SOURCE_DIR}/libs/common/src
    ${CMAKE_SOURCE_DIR}/libs/qthelpers/src
)

set_target_properties(password_manager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS password_manager
    RUNTIME DESTINATION password_manager
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES
    resources/icon.png
    DESTINATION password_manager
)
