//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include <QMainWindow>

namespace Ui {
class AccountWindow;
}

class AccountWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit AccountWindow(QWidget *parent = nullptr);
    ~AccountWindow();

  protected:
    virtual void hideEvent(QHideEvent *event) override;

  private:
    std::unique_ptr<Ui::AccountWindow> ui;

    class AccountFilterModel;
    std::unique_ptr<AccountFilterModel> model_;
};

#endif // ACCOUNTWINDOW_H
