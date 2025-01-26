# Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(money_manager PRIVATE
    datacache.h
    datacache.cpp
    moneyrecorditemmodel.h
)

target_include_directories(money_manager PRIVATE .)
