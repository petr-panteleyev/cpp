# Copyright © 2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

add_executable(password_manager_tests)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(XercesC REQUIRED COMPONENTS XercesC)
find_package(GTest REQUIRED)

target_sources(password_manager_tests PRIVATE
    serializer_test.cpp
    field_test.cpp
    ../src/serializer.cpp
    ../src/model/field.cpp
    ../src/model/card.cpp
    ../src/model/enums.cpp
)

target_include_directories(password_manager_tests PRIVATE
    ../src
    ../src/model
    ../../../include
    ../../../libs/common/src
)

qt_add_resources(password_manager_tests "xsd"
    PREFIX "/xsd"
    BASE "../resources/xsd"
    FILES "../resources/xsd/password-manager.xsd"
)

target_link_libraries(password_manager_tests PRIVATE
    Qt6::Core
    Qt6::Widgets
    XercesC::XercesC
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(password_manager_tests)
