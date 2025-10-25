//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "card.h"
#include "repository.h"

class CardRepository final : public Repository<Card> {
  public:
    CardRepository();
    ~CardRepository() = default;

  protected:
    virtual Card fromResultSet(const ResultSet &rs) const override;
    virtual void fromResultSet(const ResultSet &rs, std::vector<Card> &result) const override;
};
