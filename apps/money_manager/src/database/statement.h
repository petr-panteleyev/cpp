//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef STATEMENT_H
#define STATEMENT_H

class DatabaseConnection;

class Statement {
  public:
    explicit Statement(const DatabaseConnection &connection) noexcept;

  private:
    const DatabaseConnection &connection_;
};

#endif // STATEMENT_H
