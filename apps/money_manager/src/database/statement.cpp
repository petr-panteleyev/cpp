//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "statement.h"

Statement::Statement(const DatabaseConnection &connection) noexcept : connection_{connection} {
}
