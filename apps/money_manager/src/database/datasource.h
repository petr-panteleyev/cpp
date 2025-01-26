//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QString>
#include <memory>

class DatabaseConnection;

class DataSource final {
  public:
    explicit DataSource(const QString &server, int port, const QString &user, const QString &password,
                        const QString &database, const QString &schema);

    std::shared_ptr<DatabaseConnection> getConnection();

  private:
    QString server_;
    int port_;
    QString user_;
    QString password_;
    QString database_;
    QString schema_;
};

#endif // DATASOURCE_H
