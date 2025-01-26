//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CONTACTWINDOW_H
#define CONTACTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ContactWindow;
}

class MainWindow;

class ContactWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit ContactWindow(QWidget *parent);
    ~ContactWindow();

  protected:
    virtual void hideEvent(QHideEvent *event) override;

  private:
    MainWindow *getMainWindow() const { return reinterpret_cast<MainWindow *>(parent()); };

  private:
    std::unique_ptr<Ui::ContactWindow> ui;

    class ContactFilterModel;
    std::unique_ptr<ContactFilterModel> model_;
};

#endif // CONTACTWINDOW_H
