//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "preparedstatement.h"
#include "resultset.h"
#include "sqlexception.h"
#include <QSqlError>
#include <QSqlQuery>

PreparedStatement::PreparedStatement(std::unique_ptr<QSqlQuery> &&query) noexcept : query_{std::move(query)} {
}

std::unique_ptr<ResultSet> PreparedStatement::executeQuery() const {
    if (!query_->exec()) {
        throw SqlException(query_->lastError().text().toStdString());
    }

    return std::make_unique<ResultSet>(*query_.get());
}
