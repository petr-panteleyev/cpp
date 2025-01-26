//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "datacache.h"
#include "account.h"
#include "card.h"
#include "category.h"
#include "contact.h"
#include "currency.h"
#include "icon.h"
#include "moneyrecorditemmodel.h"
#include "transaction.h"
#include <algorithm>
#include <memory>

using std::make_unique;

class DataCacheImpl {
  public:
    template <class R>
        requires std::derived_from<R, MoneyRecord>
    std::optional<std::shared_ptr<R>> getRecord(const std::vector<std::shared_ptr<R>> &records, QUuid uuid) {
        auto found = std::find_if(records.begin(), records.end(), [&uuid](const auto &r) { return r->uuid() == uuid; });
        return (found == records.end()) ? std::nullopt : std::optional(*found);
    }

    template <class R>
        requires std::derived_from<R, MoneyRecord>
    void clear(MoneyRecordItemModel<R> *model, std::vector<std::shared_ptr<R>> &records) {
        model->beginResetModel();
        records.clear();
        model->endResetModel();
    }

    template <class R>
        requires std::derived_from<R, MoneyRecord>
    void setItems(MoneyRecordItemModel<R> *model, std::vector<std::shared_ptr<R>> &data,
                  const std::vector<std::shared_ptr<R>> &newItems) {
        model->beginResetModel();
        data.clear();
        data.reserve(newItems.size());
        data.insert(data.begin(), newItems.begin(), newItems.end());
        model->endResetModel();
    }
};

DataCache::DataCache()
    : accountItemModel_{make_unique<MoneyRecordItemModel<Account>>(accounts_)},
      cardItemModel_{make_unique<MoneyRecordItemModel<Card>>(cards_)},
      categoryItemModel_{make_unique<MoneyRecordItemModel<Category>>(categories_)},
      contactItemModel_{make_unique<MoneyRecordItemModel<Contact>>(contacts_)},
      currencyItemModel_{make_unique<MoneyRecordItemModel<Currency>>(currencies_)},
      iconItemModel_{make_unique<MoneyRecordItemModel<Icon>>(icons_)},
      transactionItemModel_{make_unique<MoneyRecordItemModel<Transaction>>(transactions_)},
      pImpl_{make_unique<DataCacheImpl>()} {
}

DataCache::~DataCache() {
}

DataCache &DataCache::cache() {
    static DataCache dataCache;
    return dataCache;
}

void DataCache::clear() {
    pImpl_->clear(reinterpret_cast<MoneyRecordItemModel<Account> *>(accountItemModel_.get()), accounts_);
    pImpl_->clear(reinterpret_cast<MoneyRecordItemModel<Card> *>(cardItemModel_.get()), cards_);
    pImpl_->clear(reinterpret_cast<MoneyRecordItemModel<Category> *>(categoryItemModel_.get()), categories_);
    pImpl_->clear(reinterpret_cast<MoneyRecordItemModel<Contact> *>(contactItemModel_.get()), contacts_);
    pImpl_->clear(reinterpret_cast<MoneyRecordItemModel<Currency> *>(currencyItemModel_.get()), currencies_);
    pImpl_->clear(reinterpret_cast<MoneyRecordItemModel<Icon> *>(iconItemModel_.get()), icons_);
    pImpl_->clear(reinterpret_cast<MoneyRecordItemModel<Transaction> *>(transactionItemModel_.get()), transactions_);
}

//
// Account
//

std::optional<std::shared_ptr<Account>> DataCache::getAccount(QUuid uuid) const {
    return pImpl_->getRecord<Account>(accounts_, uuid);
}

void DataCache::setAccounts(const std::vector<std::shared_ptr<Account>> &accounts) {
    pImpl_->setItems(reinterpret_cast<MoneyRecordItemModel<Account> *>(accountItemModel_.get()), accounts_, accounts);
}

//
// Card
//

std::optional<std::shared_ptr<Card>> DataCache::getCard(QUuid uuid) const {
    return pImpl_->getRecord<Card>(cards_, uuid);
}

void DataCache::setCards(const std::vector<std::shared_ptr<Card>> &cards) {
    pImpl_->setItems(reinterpret_cast<MoneyRecordItemModel<Card> *>(cardItemModel_.get()), cards_, cards);
}

//
// Category
//

std::optional<std::shared_ptr<Category>> DataCache::getCategory(QUuid uuid) const {
    return pImpl_->getRecord<Category>(categories_, uuid);
}

void DataCache::setCategories(const std::vector<std::shared_ptr<Category>> &categories) {
    pImpl_->setItems(reinterpret_cast<MoneyRecordItemModel<Category> *>(categoryItemModel_.get()), categories_,
                     categories);
}

//
// Contact
//

std::optional<std::shared_ptr<Contact>> DataCache::getContact(QUuid uuid) const {
    return pImpl_->getRecord<Contact>(contacts_, uuid);
}

void DataCache::setContacts(const std::vector<std::shared_ptr<Contact>> &contacts) {
    pImpl_->setItems(reinterpret_cast<MoneyRecordItemModel<Contact> *>(contactItemModel_.get()), contacts_, contacts);
}

//
// Currency
//

std::optional<std::shared_ptr<Currency>> DataCache::getCurrency(QUuid uuid) const {
    return pImpl_->getRecord<Currency>(currencies_, uuid);
}

void DataCache::setCurrencies(const std::vector<std::shared_ptr<Currency>> &currencies) {
    pImpl_->setItems(reinterpret_cast<MoneyRecordItemModel<Currency> *>(currencyItemModel_.get()), currencies_,
                     currencies);
}

//
// Icon
//

std::optional<std::shared_ptr<Icon>> DataCache::getIcon(QUuid uuid) const {
    return pImpl_->getRecord<Icon>(icons_, uuid);
}

void DataCache::setIcons(const std::vector<std::shared_ptr<Icon>> &icons) {
    pImpl_->setItems(reinterpret_cast<MoneyRecordItemModel<Icon> *>(iconItemModel_.get()), icons_, icons);
}

//
// Transaction
//

std::optional<std::shared_ptr<Transaction>> DataCache::getTransaction(QUuid uuid) const {
    return pImpl_->getRecord<Transaction>(transactions_, uuid);
}

void DataCache::setTransactions(const std::vector<std::shared_ptr<Transaction>> &transactions) {
    pImpl_->setItems(reinterpret_cast<MoneyRecordItemModel<Transaction> *>(transactionItemModel_.get()), transactions_,
                     transactions);
}
