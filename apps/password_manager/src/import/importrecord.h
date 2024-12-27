//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef IMPORTRECORD_H
#define IMPORTRECORD_H

#include "importaction.h"
#include <memory>

class Card;

class ImportRecord final {
  public:
    explicit ImportRecord(ImportAction action, const std::shared_ptr<Card> &cardToImport, bool approved) noexcept;
    explicit ImportRecord(ImportAction action, const std::shared_ptr<Card> &cardToImport) noexcept;
    explicit ImportRecord(const std::shared_ptr<Card> &cardToImport) noexcept;

    ImportAction effectiveAction() const noexcept { return approved_ ? action_ : ImportAction::SKIP; }
    void toggleApproval() noexcept { approved_ = !approved_; }

    ImportAction action() const noexcept { return action_; }
    const std::shared_ptr<Card> &cardToImport() const noexcept { return cardToImport_; }
    bool approved() const noexcept { return approved_; }

  private:
    ImportAction action_;
    const std::shared_ptr<Card> cardToImport_;
    bool approved_;
};

#endif // IMPORTRECORD_H
