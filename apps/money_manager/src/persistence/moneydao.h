//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
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
    void initialize(std::unique_ptr<DataSource> &&dataSource);
    void preload();

  public:
    static MoneyDao &dao();

  private:
    explicit MoneyDao(DataCache &cache);
    ~MoneyDao() = default;

  private:
    DataCache &cache_;

    std::unique_ptr<DataSource> dataSource_;

    std::unique_ptr<AccountRepository> accountRepository_;
    std::unique_ptr<CardRepository> cardRepository_;
    std::unique_ptr<CategoryRepository> categoryRepository_;
    std::unique_ptr<ContactRepository> contactRepository_;
    std::unique_ptr<CurrencyRepository> currencyRepository_;
    std::unique_ptr<IconRepository> iconRepository_;
    std::unique_ptr<TransactionRepository> transactionRepository_;
};

#endif // MONEYDAO_H
