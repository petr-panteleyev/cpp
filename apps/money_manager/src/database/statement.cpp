//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "statement.h"

Statement::Statement(const std::shared_ptr<DatabaseConnection> &connection) noexcept : connection_{connection}
{

}
