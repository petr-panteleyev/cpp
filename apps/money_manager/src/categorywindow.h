//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CATEGORYWINDOW_H
#define CATEGORYWINDOW_H

#include <QMainWindow>

namespace Ui {
class CategoryWindow;
}

class CategoryWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit CategoryWindow(QWidget *parent = nullptr);
    ~CategoryWindow();

  private:
    std::unique_ptr<Ui::CategoryWindow> ui;

    class CategoryFilterModel;
    std::unique_ptr<CategoryFilterModel> model_;
};

#endif // CATEGORYWINDOW_H
