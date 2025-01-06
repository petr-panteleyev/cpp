//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "observablevalue.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class AccountWindow;
class CategoryWindow;
class ConnectDialog;
class ConnectionProfileDialog;
class ConnectionProfileManager;
class ContactWindow;
class CurrencyWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    void onConnect();

  private:
    std::unique_ptr<Ui::MainWindow> ui;

    Common::ObservableValue<bool> connected_;

    std::unique_ptr<ConnectionProfileManager> profileManager_;

    // Dialogs
    ConnectionProfileDialog *connectionProfileDialog_;
    ConnectDialog *connectDialog_;

    // Windows
    AccountWindow *accountWindow_;
    CategoryWindow *categoryWindow_;
    ContactWindow *contactWindow_;
    CurrencyWindow *currencyWindow_;

    class TransactionFilterModel;
    std::unique_ptr<TransactionFilterModel> model_;
};

#endif // MAINWINDOW_H
