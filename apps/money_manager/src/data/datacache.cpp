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
#include <QUuid>
#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

using std::make_unique;

class DataCacheImpl {
  public:
    template <class R>
        requires std::derived_from<R, MoneyRecord>
    const R &getRecord(const std::vector<std::unique_ptr<R>> &records, QUuid uuid) {
        auto found = std::find_if(records.begin(), records.end(), [&uuid](const auto &r) { return r->uuid() == uuid; });
        if (found == records.end()) {
            throw std::out_of_range("Record not found");
        }
        return *found->get();
    }

    template <class R>
        requires std::derived_from<R, MoneyRecord>
    void clear(MoneyRecordItemModel *model, std::vector<std::unique_ptr<R>> &records) {
        model->beginResetModel();
        model->setSize(0);
        records.clear();
        model->endResetModel();
    }

    template <class R>
        requires std::derived_from<R, MoneyRecord>
    void setItems(MoneyRecordItemModel *model, std::vector<std::unique_ptr<R>> &data,
                  std::vector<std::unique_ptr<R>> &newItems) {
        model->beginResetModel();

        data.clear();
        data.reserve(newItems.size());
        std::for_each(std::make_move_iterator(newItems.begin()), std::make_move_iterator(newItems.end()),
                      [&data](auto item) { data.emplace_back(std::move(item)); });
        model->setSize(data.size());

        model->endResetModel();
    }
};

DataCache::DataCache()
    : accountItemModel_{make_unique<MoneyRecordItemModel>()}, cardItemModel_{make_unique<MoneyRecordItemModel>()},
      categoryItemModel_{make_unique<MoneyRecordItemModel>()}, contactItemModel_{make_unique<MoneyRecordItemModel>()},
      currencyItemModel_{make_unique<MoneyRecordItemModel>()}, iconItemModel_{make_unique<MoneyRecordItemModel>()},
      transactionItemModel_{make_unique<MoneyRecordItemModel>()}, pImpl_{make_unique<DataCacheImpl>()} {
}

DataCache::~DataCache() {
}

DataCache &DataCache::cache() {
    static DataCache dataCache;
    return dataCache;
}

void DataCache::clear() {
    pImpl_->clear(accountItemModel_.get(), accounts_);
    pImpl_->clear(cardItemModel_.get(), cards_);
    pImpl_->clear(categoryItemModel_.get(), categories_);
    pImpl_->clear(contactItemModel_.get(), contacts_);
    pImpl_->clear(currencyItemModel_.get(), currencies_);
    pImpl_->clear(iconItemModel_.get(), icons_);
    pImpl_->clear(transactionItemModel_.get(), transactions_);
}

//
// Account
//

const Account &DataCache::getAccount(const QUuid &uuid) const {
    return pImpl_->getRecord<Account>(accounts_, uuid);
}

void DataCache::setAccounts(std::vector<std::unique_ptr<Account>> &&accounts) {
    pImpl_->setItems(accountItemModel_.get(), accounts_, accounts);
}

//
// Card
//

const Card &DataCache::getCard(const QUuid &uuid) const {
    return pImpl_->getRecord<Card>(cards_, uuid);
}

void DataCache::setCards(std::vector<std::unique_ptr<Card>> &&cards) {
    pImpl_->setItems(cardItemModel_.get(), cards_, cards);
}

//
// Category
//

const Category &DataCache::getCategory(const QUuid &uuid) const {
    return pImpl_->getRecord<Category>(categories_, uuid);
}

void DataCache::setCategories(std::vector<std::unique_ptr<Category>> &&categories) {
    pImpl_->setItems(categoryItemModel_.get(), categories_, categories);
}

//
// Contact
//

const Contact &DataCache::getContact(const QUuid &uuid) const {
    return pImpl_->getRecord<Contact>(contacts_, uuid);
}

void DataCache::setContacts(std::vector<std::unique_ptr<Contact>> &&contacts) {
    pImpl_->setItems(contactItemModel_.get(), contacts_, contacts);
}

//
// Currency
//

const Currency &DataCache::getCurrency(const QUuid &uuid) const {
    return pImpl_->getRecord<Currency>(currencies_, uuid);
}

void DataCache::setCurrencies(std::vector<std::unique_ptr<Currency>> &&currencies) {
    pImpl_->setItems(currencyItemModel_.get(), currencies_, currencies);
}

//
// Icon
//

const Icon &DataCache::getIcon(const QUuid &uuid) const {
    return pImpl_->getRecord<Icon>(icons_, uuid);
}

void DataCache::setIcons(std::vector<std::unique_ptr<Icon>> &&icons) {
    pImpl_->setItems(iconItemModel_.get(), icons_, icons);
}

//
// Transaction
//

const Transaction &DataCache::getTransaction(const QUuid &uuid) const {
    return pImpl_->getRecord<Transaction>(transactions_, uuid);
}

void DataCache::setTransactions(std::vector<std::unique_ptr<Transaction>> &&transactions) {
    pImpl_->setItems(transactionItemModel_.get(), transactions_, transactions);
}
