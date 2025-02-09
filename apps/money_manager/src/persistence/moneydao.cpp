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
#include <QSqlQuery>

using std::make_unique;

MoneyDao::MoneyDao(DataCache &cache)
    : cache_{cache}, accountRepository_{make_unique<AccountRepository>()},
      cardRepository_{make_unique<CardRepository>()}, categoryRepository_{make_unique<CategoryRepository>()},
      contactRepository_{make_unique<ContactRepository>()}, currencyRepository_{make_unique<CurrencyRepository>()},
      iconRepository_{make_unique<IconRepository>()}, transactionRepository_{make_unique<TransactionRepository>()} {
}

MoneyDao &MoneyDao::dao() {
    static MoneyDao moneyDao{DataCache::cache()};
    return moneyDao;
}

void MoneyDao::initialize(std::unique_ptr<DataSource> &&dataSource) {
    dataSource_ = std::move(dataSource);
    cache_.clear();
}

void MoneyDao::preload() {
    auto conn = dataSource_->getConnection();
    auto &connRef = *conn.get();
    cache_.resetIcons([this, &connRef](auto &vec) { iconRepository_->getAll(connRef, vec); });
    cache_.resetCards([this, &connRef](auto &vec) { cardRepository_->getAll(connRef, vec); });
    cache_.resetCategories([this, &connRef](auto &vec) { categoryRepository_->getAll(connRef, vec); });
    cache_.resetAccounts([this, &connRef](auto &vec) { accountRepository_->getAll(connRef, vec); });
    cache_.resetContacts([this, &connRef](auto &vec) { contactRepository_->getAll(connRef, vec); });
    cache_.resetCurrencies([this, &connRef](auto &vec) { currencyRepository_->getAll(connRef, vec); });
    cache_.resetTransactions([this, &connRef](auto &vec) { transactionRepository_->getAll(connRef, vec); });
}
