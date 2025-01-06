# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(money_manager PRIVATE
    datasource.h
    datasource.cpp
    databaseconnection.h
    databaseconnection.cpp
    preparedstatement.h
    preparedstatement.cpp
    resultset.h
    resultset.cpp
    sqlexception.h
    statement.h
    statement.cpp
)

target_include_directories(money_manager PRIVATE .)
