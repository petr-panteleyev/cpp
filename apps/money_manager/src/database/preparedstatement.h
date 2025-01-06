//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef PREPAREDSTATEMENT_H
#define PREPAREDSTATEMENT_H

#include <memory>

class DatabaseConnection;
class ResultSet;
class QSqlQuery;

class PreparedStatement {
    friend class DatabaseConnection;

  public:
    std::shared_ptr<ResultSet> executeQuery() const;

  private:
    explicit PreparedStatement(DatabaseConnection *connection, const std::shared_ptr<QSqlQuery> &query) noexcept;

  private:
    DatabaseConnection* connection_;
    std::shared_ptr<QSqlQuery> query_;
};

#endif // PREPAREDSTATEMENT_H
