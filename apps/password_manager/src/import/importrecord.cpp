//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "importrecord.h"

ImportRecord::ImportRecord(ImportAction action, const Card &cardToImport, bool approved) noexcept
    : action_{action}, cardToImport_{&cardToImport}, approved_{approved} {
}

ImportRecord::ImportRecord(ImportAction action, const Card &cardToImport) noexcept
    : ImportRecord(action, cardToImport, true) {
}

ImportRecord::ImportRecord(const Card &cardToImport) noexcept : ImportRecord(ImportAction::ADD, cardToImport, true) {
}
