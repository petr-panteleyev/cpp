//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMPORTACTION_H
#define IMPORTACTION_H

enum class ImportAction {
    SKIP,
    REPLACE,
    ADD,
    DELETE,
    RESTORE,
};

#endif // IMPORTACTION_H
