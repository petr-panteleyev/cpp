//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "importutil.h"
#include "card.h"

namespace ImportUtil {

static void processAddition(ImportRecordVec &result, const std::shared_ptr<Card> &toImport) {
    if (toImport->active()) {
        result.push_back(std::make_shared<ImportRecord>(toImport));
    }
}

static void processUpdate(ImportRecordVec &result, const std::shared_ptr<Card> &existing, const std::shared_ptr<Card> &toImport) {
    if (existing->modified() < toImport->modified()) {
        auto action = existing->active()   ? ImportAction::REPLACE
                      : toImport->active() ? ImportAction::RESTORE
                                           : ImportAction::DELETE;
        result.push_back(std::make_shared<ImportRecord>(action, toImport));
    }
}

ImportRecordVec calculateImport(const std::vector<std::shared_ptr<Card>> &existing,
                                const std::vector<std::shared_ptr<Card>> &toImport) {
    ImportRecordVec result;

    for (auto card : toImport) {
        auto found = std::find_if(existing.begin(), existing.end(),
                                  [card](const std::shared_ptr<Card> &c) { return c->uuid() == card->uuid(); });
        if (found == existing.end()) {
            processAddition(result, card);
        } else {
            processUpdate(result, *found, card);
        }
    }

    return result;
}

} // namespace ImportUtil
