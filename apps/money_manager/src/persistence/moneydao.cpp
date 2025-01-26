//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "moneydao.h"
#include "accountrepository.h"
#include "cardrepository.h"
#include "categoryrepository.h"
#include "contactrepository.h"
#include "currencyrepository.h"
#include "datacache.h"
#include "datasource.h"
#include "iconrepository.h"
#include "transactionrepository.h"

using std::make_unique;

MoneyDao::MoneyDao(DataCache &cache)
    : cache_{cache}, accountRepository_{make_unique<AccountRepository>()},
      cardRepository_{make_unique<CardRepository>()}, categoryRepository_{make_unique<CategoryRepository>()},
      contactRepository_{make_unique<ContactRepository>()}, currencyRepository_{make_unique<CurrencyRepository>()},
      iconRepository_{make_unique<IconRepository>()}, transactionRepository_{make_unique<TransactionRepository>()} {
}

MoneyDao::~MoneyDao() {
}

MoneyDao &MoneyDao::dao() {
    static MoneyDao moneyDao{DataCache::cache()};
    return moneyDao;
}

void MoneyDao::initialize(const std::shared_ptr<DataSource> &dataSource) {
    dataSource_ = dataSource;
    cache_.clear();
}

void MoneyDao::preload() {
    auto conn = dataSource_->getConnection();
    auto &connRef = *conn.get();
    cache_.setIcons(iconRepository_->getAll(connRef));
    cache_.setCards(cardRepository_->getAll(connRef));
    cache_.setCategories(categoryRepository_->getAll(connRef));
    cache_.setAccounts(accountRepository_->getAll(connRef));
    cache_.setContacts(contactRepository_->getAll(connRef));
    cache_.setCurrencies(currencyRepository_->getAll(connRef));
    cache_.setTransactions(transactionRepository_->getAll(connRef));
}
