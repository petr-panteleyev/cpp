/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef NEWCARDDIALOG_H
#define NEWCARDDIALOG_H

#include "card.h"
#include <QDialog>

namespace Ui {
class NewCardDialog;
}

class NewCardDialog : public QDialog {
    Q_OBJECT

  public:
    explicit NewCardDialog(QWidget *parent);
    ~NewCardDialog();

    CardPtr card() const;

  private slots:
    void on_typeComboBox_currentIndexChanged(int index);

  private:
    void initTypeComboBox();
    void initPictureComboBox();

  private:
    Ui::NewCardDialog *ui;
};

#endif // NEWCARDDIALOG_H
