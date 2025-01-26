//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CATEGORYTYPE_H
#define CATEGORYTYPE_H

#include "enumclass.h"
#include <functional>

class CategoryType final : public Common::EnumClass<CategoryType> {
  public:
    static const CategoryType BANKS_AND_CASH;
    static const CategoryType INCOMES;
    static const CategoryType EXPENSES;
    static const CategoryType DEBTS;
    static const CategoryType PORTFOLIO;
    static const CategoryType ASSETS;
    static const CategoryType STARTUP;

  public:
    ~CategoryType() = default;

  private:
    explicit CategoryType(const std::string &name) : EnumClass(name) {}
};

using CategoryTypeRef = std::reference_wrapper<const CategoryType>;

const inline CategoryType CategoryType::BANKS_AND_CASH{"BANKS_AND_CASH"};
const inline CategoryType CategoryType::INCOMES{"INCOMES"};
const inline CategoryType CategoryType::EXPENSES{"EXPENSES"};
const inline CategoryType CategoryType::DEBTS{"DEBTS"};
const inline CategoryType CategoryType::PORTFOLIO{"PORTFOLIO"};
const inline CategoryType CategoryType::ASSETS{"ASSETS"};
const inline CategoryType CategoryType::STARTUP{"STARTUP"};

template <>
const inline std::vector<CategoryTypeRef> Common::EnumClass<CategoryType>::values_{
    std::cref(CategoryType::BANKS_AND_CASH), std::cref(CategoryType::INCOMES),   std::cref(CategoryType::EXPENSES),
    std::cref(CategoryType::DEBTS),          std::cref(CategoryType::PORTFOLIO), std::cref(CategoryType::ASSETS),
    std::cref(CategoryType::STARTUP),
};

#endif // CATEGORYTYPE_H
