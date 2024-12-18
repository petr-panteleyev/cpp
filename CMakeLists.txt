cmake_minimum_required(VERSION 3.23)

project(cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

# Libraries
add_subdirectory(libs/pwdgen)

# Applications
add_subdirectory(apps/password_generator)
add_subdirectory(apps/password_manager)
