//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

enum class ImportAction {
    SKIP,
    REPLACE,
    ADD,
    DELETE,
    RESTORE,
};
