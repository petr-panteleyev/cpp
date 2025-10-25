//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <memory>

class ResultSet;
class QSqlQuery;

class PreparedStatement {
    friend class DatabaseConnection;

  public:
    std::unique_ptr<ResultSet> executeQuery() const;

  private:
    explicit PreparedStatement(std::unique_ptr<QSqlQuery> &&query) noexcept;

  private:
    std::unique_ptr<QSqlQuery> query_;
};
