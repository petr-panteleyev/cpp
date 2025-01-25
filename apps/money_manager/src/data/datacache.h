//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef DATACACHE_H
#define DATACACHE_H

#include <QUuid>
#include <memory>
#include <optional>
#include <vector>

class Account;
class Category;
class Card;
class Contact;
class Currency;
class Icon;
class QAbstractItemModel;
class Transaction;

/**
 * @brief The DataCache class
 *
 * This class has global lifetime so any pointers/references are valid forever.
 */

class DataCacheImpl;

class DataCache {
  public:
    DataCache();
    ~DataCache();

    void clear();

  public:
    // Account
    std::optional<std::shared_ptr<Account>> getAccount(QUuid uuid) const;
    std::shared_ptr<Account> getAccount(int index) const { return accounts_.at(index); }
    QAbstractItemModel *getAccountItemModel() const { return accountItemModel_.get(); }
    void setAccounts(const std::vector<std::shared_ptr<Account>> &accounts);

    // Card
    std::optional<std::shared_ptr<Card>> getCard(QUuid uuid) const;
    std::shared_ptr<Card> getCard(int index) const { return cards_.at(index); }
    QAbstractItemModel *getCardItemModel() const { return cardItemModel_.get(); }
    void setCards(const std::vector<std::shared_ptr<Card>> &cards);

    // Category
    std::optional<std::shared_ptr<Category>> getCategory(QUuid uuid) const;
    std::shared_ptr<Category> getCategory(int index) const { return categories_.at(index); }
    QAbstractItemModel *getCategoryItemModel() const { return categoryItemModel_.get(); }
    void setCategories(const std::vector<std::shared_ptr<Category>> &categories);

    // Contact
    std::optional<std::shared_ptr<Contact>> getContact(QUuid uuid) const;
    std::shared_ptr<Contact> getContact(int index) const { return contacts_.at(index); }
    QAbstractItemModel *getContactItemModel() const { return contactItemModel_.get(); }
    void setContacts(const std::vector<std::shared_ptr<Contact>> &contacts);

    // Currency
    std::optional<std::shared_ptr<Currency>> getCurrency(QUuid uuid) const;
    std::shared_ptr<Currency> getCurrency(int index) const { return currencies_.at(index); }
    QAbstractItemModel *getCurrencyItemModel() const { return currencyItemModel_.get(); }
    void setCurrencies(const std::vector<std::shared_ptr<Currency>> &currencies);

    // Icon
    std::optional<std::shared_ptr<Icon>> getIcon(QUuid uuid) const;
    void setIcons(const std::vector<std::shared_ptr<Icon>> &icons);

    // Transaction
    std::optional<std::shared_ptr<Transaction>> getTransaction(QUuid uuid) const;
    std::shared_ptr<Transaction> getTransaction(int index) const { return transactions_.at(index); }
    QAbstractItemModel *getTransactionItemModel() const { return transactionItemModel_.get(); }
    void setTransactions(const std::vector<std::shared_ptr<Transaction>> &transactions);

  private:
    std::vector<std::shared_ptr<Account>> accounts_;
    std::vector<std::shared_ptr<Card>> cards_;
    std::vector<std::shared_ptr<Category>> categories_;
    std::vector<std::shared_ptr<Contact>> contacts_;
    std::vector<std::shared_ptr<Currency>> currencies_;
    std::vector<std::shared_ptr<Icon>> icons_;
    std::vector<std::shared_ptr<Transaction>> transactions_;

    // Models
    std::unique_ptr<QAbstractItemModel> accountItemModel_;
    std::unique_ptr<QAbstractItemModel> cardItemModel_;
    std::unique_ptr<QAbstractItemModel> categoryItemModel_;
    std::unique_ptr<QAbstractItemModel> contactItemModel_;
    std::unique_ptr<QAbstractItemModel> currencyItemModel_;
    std::unique_ptr<QAbstractItemModel> iconItemModel_;
    std::unique_ptr<QAbstractItemModel> transactionItemModel_;

    std::unique_ptr<DataCacheImpl> pImpl_;
};

#endif // DATACACHE_H
