//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QMainWindow>

namespace Ui {
class AccountWindow;
}

class MainWindow;

class AccountWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit AccountWindow(QWidget *parent);
    ~AccountWindow();

  protected:
    virtual void hideEvent(QHideEvent *event) override;

  private:
    MainWindow *getMainWindow() const { return reinterpret_cast<MainWindow *>(parent()); };

  private:
    std::unique_ptr<Ui::AccountWindow> ui;

    class AccountFilterModel;
    std::unique_ptr<AccountFilterModel> model_;
};
