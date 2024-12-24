//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog {
    Q_OBJECT
  public:
    enum class Mode { OPEN, IMPORT };

  public:
    explicit PasswordDialog(QWidget *parent);
    ~PasswordDialog();

    void setFileName(const QString &fileName);
    const QString getFileName() const;

    Mode getMode() const noexcept { return mode_; }
    QString getPassword() const;

    void show(Mode mode) {
        mode_ = mode;
        QDialog::show();
    }

  private:
    Ui::PasswordDialog *ui;

    Mode mode_;
};

#endif // PASSWORDDIALOG_H
