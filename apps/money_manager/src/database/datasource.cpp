//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "datasource.h"
#include "databaseconnection.h"
#include "qsqldatabase.h"
#include "sqlexception.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <memory>

namespace {

int connectionCounter = 0;

}

static const QString SEARCH_PATH{"SET search_path TO "};

DataSource::DataSource(const QString &server, int port, const QString &user, const QString &password,
                       const QString &database, const QString &schema)
    : server_{server}, port_{port}, user_{user}, password_{password}, database_{database}, schema_{schema} {
}

std::shared_ptr<DatabaseConnection> DataSource::getConnection() {
    auto connName = "conn" + QString::number(++connectionCounter);
    auto db = QSqlDatabase::addDatabase("QPSQL", connName);
    db.setHostName(server_);
    db.setPort(port_);
    db.setUserName(user_);
    db.setPassword(password_);
    db.setDatabaseName(database_);
    auto ok = db.open();
    if (!ok) {
        auto error = db.lastError();
        throw SqlException(error.text().toStdString());
    }

    QSqlQuery query{SEARCH_PATH + schema_, db};
    if (query.lastError().isValid()) {
        throw SqlException(query.lastError().text().toStdString());
    }

    db.setNumericalPrecisionPolicy(QSql::HighPrecision);
    return std::shared_ptr<DatabaseConnection>(new DatabaseConnection(connName));
}
