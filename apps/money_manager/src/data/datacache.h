//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef DATACACHE_H
#define DATACACHE_H

#include <memory>
#include <vector>

class Account;
class Category;
class Card;
class Contact;
class Currency;
class Icon;
class MoneyRecordItemModel;
class Transaction;
class QUuid;

/**
 * @brief The DataCache class
 *
 * This class has global lifetime so any pointers/references are valid forever.
 */

class DataCacheImpl;

class DataCache {
  public:
    void clear();

    // Account
    const Account &getAccount(const QUuid &uuid) const;
    const Account &getAccount(int index) const { return *accounts_.at(index); }
    MoneyRecordItemModel *getAccountItemModel() const { return accountItemModel_.get(); }
    void setAccounts(std::vector<std::unique_ptr<Account>> &&accounts);

    // Card
    const Card &getCard(const QUuid &uuid) const;
    const Card &getCard(int index) const { return *cards_.at(index); }
    MoneyRecordItemModel *getCardItemModel() const { return cardItemModel_.get(); }
    void setCards(std::vector<std::unique_ptr<Card>> &&cards);

    // Category
    const Category &getCategory(const QUuid &uuid) const;
    const Category &getCategory(int index) const { return *categories_.at(index); }
    MoneyRecordItemModel *getCategoryItemModel() const { return categoryItemModel_.get(); }
    void setCategories(std::vector<std::unique_ptr<Category>> &&categories);

    // Contact
    const Contact &getContact(const QUuid &uuid) const;
    const Contact &getContact(int index) const { return *contacts_.at(index); }
    MoneyRecordItemModel *getContactItemModel() const { return contactItemModel_.get(); }
    void setContacts(std::vector<std::unique_ptr<Contact>> &&contacts);

    // Currency
    const Currency &getCurrency(const QUuid &uuid) const;
    const Currency &getCurrency(int index) const { return *currencies_.at(index); }
    MoneyRecordItemModel *getCurrencyItemModel() const { return currencyItemModel_.get(); }
    void setCurrencies(std::vector<std::unique_ptr<Currency>> &&currencies);

    // Icon
    const Icon &getIcon(const QUuid &uuid) const;
    void setIcons(std::vector<std::unique_ptr<Icon>> &&icons);

    // Transaction
    const Transaction &getTransaction(const QUuid &uuid) const;
    const Transaction &getTransaction(int index) const { return *transactions_.at(index); }
    MoneyRecordItemModel *getTransactionItemModel() const { return transactionItemModel_.get(); }
    void setTransactions(std::vector<std::unique_ptr<Transaction>> &&transactions);

  public:
    static DataCache &cache();

  private:
    DataCache();
    ~DataCache();

  private:
    std::vector<std::unique_ptr<Account>> accounts_;
    std::vector<std::unique_ptr<Card>> cards_;
    std::vector<std::unique_ptr<Category>> categories_;
    std::vector<std::unique_ptr<Contact>> contacts_;
    std::vector<std::unique_ptr<Currency>> currencies_;
    std::vector<std::unique_ptr<Icon>> icons_;
    std::vector<std::unique_ptr<Transaction>> transactions_;

    // Models
    std::unique_ptr<MoneyRecordItemModel> accountItemModel_;
    std::unique_ptr<MoneyRecordItemModel> cardItemModel_;
    std::unique_ptr<MoneyRecordItemModel> categoryItemModel_;
    std::unique_ptr<MoneyRecordItemModel> contactItemModel_;
    std::unique_ptr<MoneyRecordItemModel> currencyItemModel_;
    std::unique_ptr<MoneyRecordItemModel> iconItemModel_;
    std::unique_ptr<MoneyRecordItemModel> transactionItemModel_;

    std::unique_ptr<DataCacheImpl> pImpl_;
};

#endif // DATACACHE_H
