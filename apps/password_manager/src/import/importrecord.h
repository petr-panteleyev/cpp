/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef IMPORTRECORD_H
#define IMPORTRECORD_H

#include "card.h"
#include <memory>
#include <vector>

enum class ImportAction { SKIP, REPLACE, ADD, DELETE, RESTORE };

class ImportRecord final {
  public:
    explicit ImportRecord(ImportAction action, const CardPtr &cardToImport, bool approved) noexcept
        : action_{action}, cardToImport_{cardToImport}, approved_{approved} {}

    explicit ImportRecord(ImportAction action, const CardPtr &cardToImport) noexcept
        : ImportRecord(action, cardToImport, true) {}

    explicit ImportRecord(const CardPtr &cardToImport) noexcept : ImportRecord(ImportAction::ADD, cardToImport, true) {}

    ImportAction effectiveAction() const noexcept { return approved_ ? action_ : ImportAction::SKIP; }
    void         toggleApproval() noexcept { approved_ = !approved_; }

    ImportAction   action() const noexcept { return action_; }
    const CardPtr &cardToImport() const noexcept { return cardToImport_; }
    bool           approved() const noexcept { return approved_; }

  private:
    ImportAction  action_;
    const CardPtr cardToImport_;
    bool          approved_;
};

using ImportRecordPtr = std::shared_ptr<ImportRecord>;
using ImportRecordVec = std::vector<ImportRecordPtr>;

#endif // IMPORTRECORD_H
