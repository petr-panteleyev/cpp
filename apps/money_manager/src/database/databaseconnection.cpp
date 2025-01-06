//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "databaseconnection.h"
#include "preparedstatement.h"
#include "sqlexception.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <memory>

DatabaseConnection::DatabaseConnection(const QString &name) noexcept : name_{name} {
}

DatabaseConnection::~DatabaseConnection() {
    {
        auto db = QSqlDatabase::database(name_);
        if (!db.isValid()) {
            return;
        }
        if (db.isOpen()) {
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(name_);
}

std::shared_ptr<PreparedStatement> DatabaseConnection::prepareStatement(const QString &sql) {
    auto db = QSqlDatabase::database(name_);

    auto query = std::make_shared<QSqlQuery>(db);
    query->prepare(sql);
    if (query->lastError().isValid()) {
        throw SqlException(query->lastError().text().toStdString());
    }

    return std::shared_ptr<PreparedStatement>(new PreparedStatement(this, query));
}
