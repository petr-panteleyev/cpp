# Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
# SPDX-License-Identifier: BSD-2-Clause

target_sources(money_manager PRIVATE
    account.h
    account.cpp
    card.h
    card.cpp
    cardtype.h
    category.h
    category.cpp
    categorytype.h
    contact.h
    contact.cpp
    contacttype.h
    currency.h
    currency.cpp
    icon.h
    icon.cpp
    moneyrecord.h
    moneyrecord.cpp
    transaction.h
    transaction.cpp
    transactiondetail.h
    transactiondetail.cpp
)

target_include_directories(money_manager PRIVATE .)
