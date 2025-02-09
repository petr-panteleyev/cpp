//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "datacache.h"
#include "moneyrecorditemmodel.h"
#include <QUuid>
#include <memory>

using std::make_unique;

DataCache::DataCache()
    : accountItemModel_{make_unique<MoneyRecordItemModel<Account>>(accounts_)},
      cardItemModel_{make_unique<MoneyRecordItemModel<Card>>(cards_)},
      categoryItemModel_{make_unique<MoneyRecordItemModel<Category>>(categories_)},
      contactItemModel_{make_unique<MoneyRecordItemModel<Contact>>(contacts_)},
      currencyItemModel_{make_unique<MoneyRecordItemModel<Currency>>(currencies_)},
      iconItemModel_{make_unique<MoneyRecordItemModel<Icon>>(icons_)},
      transactionItemModel_{make_unique<MoneyRecordItemModel<Transaction>>(transactions_)} {
}

DataCache &DataCache::cache() {
    static DataCache dataCache;
    return dataCache;
}

void DataCache::clear() {
    accountItemModel_->clear();
    cardItemModel_->clear();
    categoryItemModel_->clear();
    contactItemModel_->clear();
    currencyItemModel_->clear();
    iconItemModel_->clear();
    transactionItemModel_->clear();
}
