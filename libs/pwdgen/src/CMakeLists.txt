# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

add_library(pwdgen STATIC)

target_compile_options(pwdgen PRIVATE
    -Werror
    -Wall
    -pedantic
)

target_sources(pwdgen
    PUBLIC
        generator.h
    PRIVATE
        characterset.h
        characterset.cpp
        generator.cpp
)
