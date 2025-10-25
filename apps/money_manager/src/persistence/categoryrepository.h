//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "category.h"
#include "repository.h"

class CategoryRepository final : public Repository<Category> {
  public:
    CategoryRepository();
    ~CategoryRepository() = default;

  protected:
    virtual Category fromResultSet(const ResultSet &rs) const override;
    virtual void fromResultSet(const ResultSet &rs, std::vector<Category> &result) const override;
};
