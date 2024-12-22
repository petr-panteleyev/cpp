# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(password_manager PRIVATE
    card.h
    card.cpp
    cardclass.h
    creditcardtype.h
    enums.cpp
    field.h
    field.cpp
    fieldtype.h
    picture.h
    picture.cpp
    recordtype.h
)
target_include_directories(password_manager PRIVATE .)
