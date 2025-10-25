//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "importaction.h"

class Card;

class ImportRecord final {
  public:
    explicit ImportRecord(ImportAction action, const Card &cardToImport, bool approved) noexcept
        : action_{action}, cardToImport_{&cardToImport}, approved_{approved} {}
    explicit ImportRecord(ImportAction action, const Card &cardToImport) noexcept
        : ImportRecord(action, cardToImport, true) {}
    explicit ImportRecord(const Card &cardToImport) noexcept : ImportRecord(ImportAction::ADD, cardToImport, true) {}

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
