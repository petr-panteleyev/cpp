//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMPORTRECORD_H
#define IMPORTRECORD_H

#include "importaction.h"

class Card;

class ImportRecord final {
  public:
    explicit ImportRecord(ImportAction action, const Card &cardToImport, bool approved) noexcept;
    explicit ImportRecord(ImportAction action, const Card &cardToImport) noexcept;
    explicit ImportRecord(const Card &cardToImport) noexcept;

    ImportAction effectiveAction() const noexcept { return approved_ ? action_ : ImportAction::SKIP; }
    void toggleApproval() noexcept { approved_ = !approved_; }

    ImportAction action() const noexcept { return action_; }
    const Card *cardToImport() const noexcept { return cardToImport_; }
    bool approved() const noexcept { return approved_; }

  private:
    ImportAction action_;
    const Card *cardToImport_;
    bool approved_;
};

#endif // IMPORTRECORD_H
