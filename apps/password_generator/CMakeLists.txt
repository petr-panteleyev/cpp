cmake_minimum_required(VERSION 3.5)

project(password_generator VERSION 24.11.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES src/ui/password_generator_ru.ts)

set(PROJECT_SOURCES
        src/main.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
        src/generator/generator.cpp
        src/generator/generator.h
        src/generator/character_set.cpp
        src/generator/character_set.h
)

set(RESOURCE_FILES
    resources/icon.png
)

qt_add_executable(password_generator
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_compile_options(password_generator PRIVATE
    -Werror
    -Wall
    -Wpedantic
)

qt_add_resources(password_generator "resources"
    PREFIX "/images"
    BASE "resources"
    FILES ${RESOURCE_FILES}
)

qt_add_translations(password_generator
    INCLUDE_DIRECTORIES
        ${PROJECT_SOURCE_DIR}
    TS_FILES
        ${TS_FILES})
add_dependencies(password_generator update_translations)

target_link_libraries(password_generator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(password_generator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS password_generator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(password_generator)
