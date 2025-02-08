//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef ICONREPOSITORY_H
#define ICONREPOSITORY_H

#include "icon.h"
#include "repository.h"

class IconRepository final : public Repository<Icon> {
  public:
    IconRepository();
    ~IconRepository() = default;

  protected:
    virtual std::unique_ptr<Icon> fromResultSet(const ResultSet &rs) const override;
};

#endif // ICONREPOSITORY_H
