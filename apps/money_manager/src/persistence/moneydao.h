//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef MONEYDAO_H
#define MONEYDAO_H

#include <memory>

class AccountRepository;
class CardRepository;
class CategoryRepository;
class DataCache;
class DataSource;
class ContactRepository;
class CurrencyRepository;
class IconRepository;
class TransactionRepository;

class MoneyDao final {
  public:
    explicit MoneyDao(DataCache &cache);
    ~MoneyDao();

    void initialize(const std::shared_ptr<DataSource> &dataSource);
    void preload();

  private:
    DataCache &cache_;

    std::shared_ptr<DataSource> dataSource_;

    std::unique_ptr<AccountRepository> accountRepository_;
    std::unique_ptr<CardRepository> cardRepository_;
    std::unique_ptr<CategoryRepository> categoryRepository_;
    std::unique_ptr<ContactRepository> contactRepository_;
    std::unique_ptr<CurrencyRepository> currencyRepository_;
    std::unique_ptr<IconRepository> iconRepository_;
    std::unique_ptr<TransactionRepository> transactionRepository_;
};

#endif // MONEYDAO_H
