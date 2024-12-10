/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CARDEDITDIALOG_H
#define CARDEDITDIALOG_H

#include "editfieldlistmodel.h"
#include <QDialog>
#include <card.h>

namespace Ui {
class CardEditDialog;
}

class CardEditDialog : public QDialog {
    Q_OBJECT

  public:
    explicit CardEditDialog(const Card &card, QWidget *parent = nullptr);
    ~CardEditDialog();

    const Card &card() const { return card_; }

    virtual void done(int code) override;

  private:
    void initPictureComboBox();

  private:
    Ui::CardEditDialog *ui;

    Card               card_;
    EditFieldListModel fieldTableModel_;
};

#endif // CARDEDITDIALOG_H
