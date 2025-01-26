//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <memory>
#include <QString>

class PreparedStatement;

class DatabaseConnection final {
    friend class DataSource;
    friend class PreparedStatement;

  public:
    ~DatabaseConnection();

    std::shared_ptr<PreparedStatement> prepareStatement(const QString &sql);

  private:
    explicit DatabaseConnection(const QString &name) noexcept;

    const QString &name() const noexcept { return name_; }

  private:
    QString name_;
};

#endif // DATABASECONNECTION_H
