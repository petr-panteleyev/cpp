# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.23)

project(cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")

include(CTest)

# Libraries
add_subdirectory(libs/pwdgen)
add_subdirectory(libs/common)

# Applications
add_subdirectory(apps/password_generator)
add_subdirectory(apps/password_manager)
add_subdirectory(apps/sapper)
