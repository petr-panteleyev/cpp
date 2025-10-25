//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "account.h"
#include "card.h"
#include "category.h"
#include "contact.h"
#include "currency.h"
#include "icon.h"
#include "moneyrecorditemmodel.h"
#include "transaction.h"
#include <functional>
#include <memory>
#include <vector>

class QUuid;

/**
 * @brief The DataCache class
 *
 * This class has global lifetime so any pointers/references are valid forever.
 */

class DataCache {
  public:
    void clear();

    // Account
    const Account &getAccount(const QUuid &uuid) const { return accountItemModel_->getRecord(uuid); }
    const Account &getAccount(int index) const { return accounts_.at(index); }
    MoneyRecordItemModel<Account> *getAccountItemModel() const { return accountItemModel_.get(); }
    void resetAccounts(const std::function<void(std::vector<Account> &)> &dataSupplier) {
        accountItemModel_->resetItems(dataSupplier);
    }

    // Card
    const Card &getCard(const QUuid &uuid) const { return cardItemModel_->getRecord(uuid); }
    const Card &getCard(int index) const { return cards_.at(index); }
    MoneyRecordItemModel<Card> *getCardItemModel() const { return cardItemModel_.get(); }
    void resetCards(const std::function<void(std::vector<Card> &)> &dataSupplier) {
        cardItemModel_->resetItems(dataSupplier);
    }

    // Category
    const Category &getCategory(const QUuid &uuid) const { return categoryItemModel_->getRecord(uuid); }
    const Category &getCategory(int index) const { return categories_.at(index); }
    MoneyRecordItemModel<Category> *getCategoryItemModel() const { return categoryItemModel_.get(); }
    void resetCategories(const std::function<void(std::vector<Category> &)> &dataSupplier) {
        categoryItemModel_->resetItems(dataSupplier);
    }

    // Contact
    const Contact &getContact(const QUuid &uuid) const { return contactItemModel_->getRecord(uuid); }
    const Contact &getContact(int index) const { return contacts_.at(index); }
    MoneyRecordItemModel<Contact> *getContactItemModel() const { return contactItemModel_.get(); }
    void resetContacts(const std::function<void(std::vector<Contact> &)> &dataSupplier) {
        contactItemModel_->resetItems(dataSupplier);
    }

    // Currency
    const Currency &getCurrency(const QUuid &uuid) const { return currencyItemModel_->getRecord(uuid); }
    const Currency &getCurrency(int index) const { return currencies_.at(index); }
    MoneyRecordItemModel<Currency> *getCurrencyItemModel() const { return currencyItemModel_.get(); }
    void resetCurrencies(const std::function<void(std::vector<Currency> &)> &dataSupplier) {
        currencyItemModel_->resetItems(dataSupplier);
    }

    // Icon
    const Icon &getIcon(const QUuid &uuid) const { return iconItemModel_->getRecord(uuid); }
    void resetIcons(const std::function<void(std::vector<Icon> &)> &dataSupplier) {
        iconItemModel_->resetItems(dataSupplier);
    }

    // Transaction
    const Transaction &getTransaction(const QUuid &uuid) const { return transactionItemModel_->getRecord(uuid); }
    const Transaction &getTransaction(int index) const { return transactions_.at(index); }
    MoneyRecordItemModel<Transaction> *getTransactionItemModel() const { return transactionItemModel_.get(); }
    void resetTransactions(const std::function<void(std::vector<Transaction> &)> &dataSupplier) {
        transactionItemModel_->resetItems(dataSupplier);
    }

  public:
    static DataCache &cache();

  private:
    DataCache();
    ~DataCache() = default;

  private:
    std::vector<Account> accounts_;
    std::vector<Card> cards_;
    std::vector<Category> categories_;
    std::vector<Contact> contacts_;
    std::vector<Currency> currencies_;
    std::vector<Icon> icons_;
    std::vector<Transaction> transactions_;

    // Models
    std::unique_ptr<MoneyRecordItemModel<Account>> accountItemModel_;
    std::unique_ptr<MoneyRecordItemModel<Card>> cardItemModel_;
    std::unique_ptr<MoneyRecordItemModel<Category>> categoryItemModel_;
    std::unique_ptr<MoneyRecordItemModel<Contact>> contactItemModel_;
    std::unique_ptr<MoneyRecordItemModel<Currency>> currencyItemModel_;
    std::unique_ptr<MoneyRecordItemModel<Icon>> iconItemModel_;
    std::unique_ptr<MoneyRecordItemModel<Transaction>> transactionItemModel_;
};
