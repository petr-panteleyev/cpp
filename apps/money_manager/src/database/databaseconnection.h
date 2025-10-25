//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QString>
#include <memory>

class PreparedStatement;

class DatabaseConnection final {
    friend class DataSource;
    friend class PreparedStatement;

  public:
    ~DatabaseConnection();

    std::unique_ptr<PreparedStatement> prepareStatement(const QString &sql);

  private:
    explicit DatabaseConnection(const QString &name) noexcept;

    const QString &name() const noexcept { return name_; }

  private:
    QString name_;
};
