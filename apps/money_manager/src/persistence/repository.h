//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "databaseconnection.h"
#include "moneyrecord.h"
#include "preparedstatement.h"
#include "resultset.h"
#include <QString>
#include <vector>

template <class R>
    requires std::derived_from<R, MoneyRecord>
class Repository {
  public:
    void getAll(DatabaseConnection &conn, std::vector<R> &result) {
        auto st = conn.prepareStatement("SELECT * FROM " + tableName_);
        auto rs = st->executeQuery();
        if (rs->rows() > 0) {
            result.reserve(rs->rows());
        }
        while (rs->next()) {
            fromResultSet(*rs.get(), result);
        }
    }

    std::vector<R> getAll(DatabaseConnection &conn) {
        std::vector<R> result;
        getAll(conn, result);
        return result;
    }

  protected:
    explicit Repository(const QString &tableName) : tableName_{tableName} {}
    virtual ~Repository() = default;

    virtual R fromResultSet(const ResultSet &rs) const = 0;
    virtual void fromResultSet(const ResultSet &rs, std::vector<R> &result) const = 0;

  private:
    QString tableName_;
};

#endif // REPOSITORY_H
