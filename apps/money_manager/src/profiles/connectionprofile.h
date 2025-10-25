//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "datasource.h"
#include <QString>

class ConnectionProfile final {
  public:
    explicit ConnectionProfile(const QString &name, const QString &host, int port, const QString &user,
                               const QString &password, const QString &database, const QString schema);
    explicit ConnectionProfile(const QString &name, const QString &database, const QString &schema);
    explicit ConnectionProfile(const ConnectionProfile &profile);

    const QString &name() const noexcept { return name_; }
    const QString &host() const noexcept { return host_; }
    int port() const noexcept { return port_; }
    const QString &user() const noexcept { return user_; }
    const QString &password() const noexcept { return password_; }
    const QString &database() const noexcept { return database_; }
    const QString &schema() const noexcept { return schema_; }

    std::unique_ptr<DataSource> createDataSource() const noexcept;

  private:
    QString name_;
    QString host_;
    int port_;
    QString user_;
    QString password_;
    QString database_;
    QString schema_;
};
