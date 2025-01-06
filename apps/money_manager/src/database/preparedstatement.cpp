//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "preparedstatement.h"
#include "databaseconnection.h"
#include "resultset.h"
#include "sqlexception.h"
#include <QSqlError>
#include <QSqlQuery>

PreparedStatement::PreparedStatement(DatabaseConnection *connection, const std::shared_ptr<QSqlQuery> &query) noexcept
    : connection_{connection}, query_{query} {
}

std::shared_ptr<ResultSet> PreparedStatement::executeQuery() const {
    if (!query_->exec()) {
        throw SqlException(query_->lastError().text().toStdString());
    }

    return std::make_shared<ResultSet>(query_);
}
