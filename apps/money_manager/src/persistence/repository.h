//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "databaseconnection.h"
#include "moneyrecord.h"
#include "preparedstatement.h"
#include "resultset.h"
#include <QString>
#include <memory>
#include <vector>

template <class R>
    requires std::derived_from<R, MoneyRecord>
class Repository {

  public:
    std::vector<std::unique_ptr<R>> getAll(DatabaseConnection &conn) {
        auto st = conn.prepareStatement("SELECT * FROM " + tableName_);
        std::vector<std::unique_ptr<R>> result;
        auto rs = st->executeQuery();
        while (rs->next()) {
            result.push_back(fromResultSet(*rs.get()));
        }
        return result;
    }

  protected:
    explicit Repository(const QString &tableName) : tableName_{tableName} {}
    virtual ~Repository() = default;

    virtual std::unique_ptr<R> fromResultSet(const ResultSet &rs) const = 0;

  private:
    QString tableName_;
};

#endif // REPOSITORY_H
