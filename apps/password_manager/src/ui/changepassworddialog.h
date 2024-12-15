/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ChangePasswordDialog(QWidget *parent);
    ~ChangePasswordDialog();

    void reset(const QString &fileName);

    QString password() const;

    virtual void done(int code) override;

  private:
    void setEditBackground(bool disabled);

  private slots:
    void on_passwordEdit_textChanged(const QString &text);
    void on_repeatEdit_textChanged(const QString &text);

  private:
    Ui::ChangePasswordDialog *ui;

    QPalette enabledColors_;
    QPalette disabledColors_;
};

#endif // CHANGEPASSWORDDIALOG_H
