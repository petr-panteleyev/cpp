//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "importutil.h"
#include "card.h"
#include "importrecord.h"

using ImportRecordVec = std::vector<std::unique_ptr<ImportRecord>>;

namespace ImportUtil {

static void processAddition(std::vector<ImportRecord> &result, const Card &toImport) {
    if (toImport.active()) {
        result.push_back(ImportRecord(toImport));
    }
}

static void processUpdate(std::vector<ImportRecord> &result, const Card &existing, const Card &toImport) {
    if (existing.modified() < toImport.modified()) {
        auto action = existing.active()   ? ImportAction::REPLACE
                      : toImport.active() ? ImportAction::RESTORE
                                          : ImportAction::DELETE;
        result.push_back(ImportRecord(action, toImport));
    }
}

std::vector<ImportRecord> calculateImport(const std::vector<Card> &existing, const std::vector<Card> &toImport) {
    std::vector<ImportRecord> result;

    for (const auto &card : toImport) {
        auto found =
            std::find_if(existing.begin(), existing.end(), [&card](const Card &c) { return c.uuid() == card.uuid(); });
        if (found == existing.end()) {
            processAddition(result, card);
        } else {
            processUpdate(result, *found, card);
        }
    }

    return result;
}

} // namespace ImportUtil
