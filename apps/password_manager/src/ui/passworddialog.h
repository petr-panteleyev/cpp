/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog {
    Q_OBJECT

  public:
    explicit PasswordDialog(QWidget *parent, const QString &fileName);
    ~PasswordDialog();

    QString password() const;

  private:
    Ui::PasswordDialog *ui;
};

#endif // PASSWORDDIALOG_H
