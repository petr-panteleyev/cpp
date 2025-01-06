# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(money_manager PRIVATE
    accountrepository.h
    accountrepository.cpp
    cardrepository.h
    cardrepository.cpp
    categoryrepository.h
    categoryrepository.cpp
    contactrepository.h
    contactrepository.cpp
    currencyrepository.h
    currencyrepository.cpp
    iconrepository.h
    iconrepository.cpp
    moneydao.h
    moneydao.cpp
    repository.h
    transactionrepository.h
    transactionrepository.cpp
)

target_include_directories(money_manager PRIVATE .)
