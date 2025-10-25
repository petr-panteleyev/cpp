//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QDialog>

namespace Ui {
class ConnectionProfileDialog;
}

class ConnectionProfileManager;

class ConnectionProfileDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ConnectionProfileDialog(QWidget *parent, ConnectionProfileManager *profileManager);
    ~ConnectionProfileDialog();

  private:
    void onNewButton();
    void onDeleteButton();
    void onSaveButton();
    void onTestButton();
    void onCurrentProfileChanged(const QModelIndex &current, const QModelIndex &previous);

  private:
    std::unique_ptr<Ui::ConnectionProfileDialog> ui;

    ConnectionProfileManager *profileManager_;
};
