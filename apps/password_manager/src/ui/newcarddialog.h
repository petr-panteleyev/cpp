//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef NEWCARDDIALOG_H
#define NEWCARDDIALOG_H

#include "card.h"
#include <QDialog>
#include <memory>

namespace Ui {
class NewCardDialog;
}

class Card;

class NewCardDialog : public QDialog {
    Q_OBJECT

  public:
    explicit NewCardDialog(QWidget *parent);
    ~NewCardDialog();

    Card card() const;

  private:
    void onTypeComboBoxCurrentIndexChanged(int index);

  private:
    std::unique_ptr<Ui::NewCardDialog> ui;
};

#endif // NEWCARDDIALOG_H
