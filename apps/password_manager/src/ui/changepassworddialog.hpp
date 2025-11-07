//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

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

  private:
    std::unique_ptr<Ui::ChangePasswordDialog> ui;

    QPalette enabledColors_;
    QPalette disabledColors_;
};
