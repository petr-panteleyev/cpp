# Copyright © 2025 Petr Panteleyev
# SPDX-License-Identifier: BSD-2-Clause

project(cryptography VERSION 1.0.0 LANGUAGES CXX)

find_package(OpenSSL REQUIRED COMPONENTS Crypto)
find_package(GTest REQUIRED)

#
# Library
#

add_library(cryptography STATIC)

target_compile_options(cryptography PRIVATE -Werror -Wall -pedantic)

target_sources(cryptography
    PUBLIC
        FILE_SET CXX_MODULES
            TYPE CXX_MODULES
            FILES
                src/crypto.cxx
    PRIVATE
        src/aes256.cpp
)

#
# Tests
#

add_executable(cryptography_tests)

FILE(GLOB_RECURSE test_sources "test/*.cpp")
target_sources(cryptography_tests PRIVATE ${test_sources})

target_include_directories(cryptography_tests PRIVATE src)

target_link_libraries(cryptography_tests PRIVATE
    cryptography
    OpenSSL::Crypto
    ${GTEST_LIBRARIES}
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(cryptography_tests)
