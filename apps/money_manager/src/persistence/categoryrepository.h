//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H

#include "category.h"
#include "repository.h"

class CategoryRepository final : public Repository<Category> {
  public:
    CategoryRepository();
    ~CategoryRepository() = default;

  protected:
    virtual std::shared_ptr<Category> fromResultSet(const ResultSet &rs) const override;
};

#endif // CATEGORYREPOSITORY_H
