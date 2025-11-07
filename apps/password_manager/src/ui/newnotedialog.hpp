//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "card.hpp"
#include <QDialog>
#include <memory>

namespace Ui {
class NewNoteDialog;
}

class NewNoteDialog : public QDialog {
    Q_OBJECT

  public:
    explicit NewNoteDialog(QWidget *parent);
    ~NewNoteDialog();

    Card note() const;

  private:
    std::unique_ptr<Ui::NewNoteDialog> ui;
};
