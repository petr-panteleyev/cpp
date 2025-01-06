//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>

class DatabaseConnection;

class Statement {
  public:
    explicit Statement(const std::shared_ptr<DatabaseConnection> &connection) noexcept;

  private:
    std::shared_ptr<DatabaseConnection> connection_;
};

#endif // STATEMENT_H
