cmake_minimum_required(VERSION 3.5)

project(password_manager VERSION 24.12.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Widgets LinguistTools Xml)
find_package(OpenSSL REQUIRED)

set(TS_FILES src/ui/password_manager_ru_RU.ts)

set(PROJECT_SOURCES
    src/main.cpp
    src/serializer.h
    src/serializer.cpp
    src/exceptions.h
    src/version.h
)

include(src/model/model.cmake)
include(src/ui/ui.cmake)
include(src/crypto/crypto.cmake)
include(../../include/include.cmake)

file(GLOB RESOURCE_FILES "resources/*.png")

qt_add_executable(password_manager
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_compile_options(password_manager PRIVATE
    -Werror
    -Wall
    -Wpedantic
)

target_compile_definitions(password_manager
                           PRIVATE "PROJECT_VERSION=${PROJECT_VERSION}")

qt_add_resources(password_manager "resources"
    PREFIX "/images"
    BASE "resources"
    FILES ${RESOURCE_FILES}
)

qt_add_translations(password_manager
    INCLUDE_DIRECTORIES
        ${PROJECT_SOURCE_DIR}
    TS_FILES
        ${TS_FILES})
add_dependencies(password_manager update_translations)

target_link_libraries(password_manager PRIVATE Qt6::Core Qt6::Widgets Qt6::Xml OpenSSL::Crypto)
target_include_directories(password_manager PRIVATE
  src
  src/model
  src/ui
  src/crypto
  ../../include
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
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(password_manager)
