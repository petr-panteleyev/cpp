//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <memory>

namespace Ui {
class ConnectDialog;
}

class ConnectionProfile;
class ConnectionProfileManager;

class ConnectDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ConnectDialog(QWidget *parent, ConnectionProfileManager *profileManager);
    ~ConnectDialog();

    const ConnectionProfile &profile() const;

  private:
    std::unique_ptr<Ui::ConnectDialog> ui;
    ConnectionProfileManager *profileManager_;
};

#endif // CONNECTDIALOG_H
