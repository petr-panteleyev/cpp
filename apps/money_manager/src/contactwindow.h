//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CONTACTWINDOW_H
#define CONTACTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ContactWindow;
}

class ContactWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit ContactWindow(QWidget *parent = nullptr);
    ~ContactWindow();

  private:
    std::unique_ptr<Ui::ContactWindow> ui;

    class ContactFilterModel;
    std::unique_ptr<ContactFilterModel> model_;
};

#endif // CONTACTWINDOW_H
