//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CONTACTREPOSITORY_H
#define CONTACTREPOSITORY_H

#include "contact.h"
#include "repository.h"

class ContactRepository final : public Repository<Contact> {
  public:
    ContactRepository();
    ~ContactRepository() = default;

  protected:
    virtual Contact fromResultSet(const ResultSet &rs) const override;
    virtual void fromResultSet(const ResultSet &rs, std::vector<Contact> &result) const override;
};

#endif // CONTACTREPOSITORY_H
