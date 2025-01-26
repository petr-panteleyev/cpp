# Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

add_library(common STATIC)

target_compile_options(common PRIVATE
    -Werror
    -Wall
    -pedantic
)

target_sources(common
    PUBLIC
        arithmeticexception.h
        decimal.h
        enumclass.h
        observablevalue.h
    PRIVATE
        decimal.cpp
)
