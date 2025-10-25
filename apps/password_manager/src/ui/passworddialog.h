//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QDialog>
#include <memory>

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
    std::unique_ptr<Ui::PasswordDialog> ui;

    Mode mode_;
};
