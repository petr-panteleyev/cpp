//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

class DatabaseConnection;

class Statement {
  public:
    explicit Statement(const DatabaseConnection &connection) noexcept;

  private:
    const DatabaseConnection &connection_;
};
