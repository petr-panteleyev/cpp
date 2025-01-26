//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "connectionprofile.h"
#include "datasource.h"

ConnectionProfile::ConnectionProfile(const QString &name, const QString &host, int port, const QString &user,
                                     const QString &password, const QString &database, const QString schema)
    : name_{name}, host_{host}, port_{port}, user_{user}, password_{password}, database_{database}, schema_{schema} {
}

ConnectionProfile::ConnectionProfile(const QString &name, const QString &database, const QString &schema)
    : ConnectionProfile(name, "localhost", 5432, "", "", database, schema) {
}

ConnectionProfile::ConnectionProfile(const ConnectionProfile &profile)
    : name_{profile.name_}, host_{profile.host_}, port_{profile.port_}, user_{profile.user_},
      password_{profile.password_}, database_{profile.database_}, schema_{profile.schema_} {
}

std::shared_ptr<DataSource> ConnectionProfile::createDataSource() const noexcept {
    return std::make_shared<DataSource>(host_, port_, user_, password_, database_, schema_);
}
