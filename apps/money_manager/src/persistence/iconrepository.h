//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "icon.h"
#include "repository.h"

class IconRepository final : public Repository<Icon> {
  public:
    IconRepository();
    ~IconRepository() = default;

  protected:
    virtual Icon fromResultSet(const ResultSet &rs) const override;
    virtual void fromResultSet(const ResultSet &rs, std::vector<Icon> &result) const override;
};
