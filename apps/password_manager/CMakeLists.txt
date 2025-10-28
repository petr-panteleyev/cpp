# Copyright © 2024-2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(password_manager VERSION 25.10.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(OpenSSL REQUIRED COMPONENTS Crypto)
find_package(XercesC REQUIRED COMPONENTS XercesC)
find_package(GTest REQUIRED)

#
# Executable
#

FILE(GLOB_RECURSE headers "src/*.h" "src/*.hpp")
FILE(GLOB_RECURSE sources "src/*.cpp" "src/*.ui")
qt_add_executable(password_manager ${headers} ${sources})

target_compile_options(password_manager PRIVATE -Werror -Wall -pedantic)

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

qt_add_resources(password_manager "xsd"
    PREFIX "/xsd"
    BASE "resources/xsd"
    FILES "resources/xsd/password-manager.xsd"
)

target_link_libraries(password_manager PRIVATE 
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    OpenSSL::Crypto
    XercesC::XercesC
    pwdgen
    qthelpers
    cryptography
)

target_include_directories(password_manager PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/pwdgen/src
    ${CMAKE_SOURCE_DIR}/libs/common/src
    ${CMAKE_SOURCE_DIR}/libs/qthelpers/src
    src
    src/import
    src/model
    src/settings
    src/ui
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

#
# Test
#

add_executable(password_manager_tests)

FILE(GLOB_RECURSE test_sources "test/*.cpp")
target_sources(password_manager_tests PRIVATE
    ${test_sources}
    src/serializer.cpp
    src/model/field.cpp
    src/model/card.cpp
    src/model/enums.cpp
)

target_include_directories(password_manager_tests PRIVATE
    src
    src/model
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/common/src
)

qt_add_resources(password_manager_tests "xsd"
    PREFIX "/xsd"
    BASE "resources/xsd"
    FILES "resources/xsd/password-manager.xsd"
)

target_link_libraries(password_manager_tests PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    XercesC::XercesC
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(password_manager_tests)
