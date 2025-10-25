//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QMainWindow>

namespace Ui {
class CategoryWindow;
}

class MainWindow;

class CategoryWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit CategoryWindow(QWidget *parent);
    ~CategoryWindow();

  protected:
    virtual void hideEvent(QHideEvent *event) override;

  private:
    MainWindow *getMainWindow() const { return reinterpret_cast<MainWindow *>(parent()); };

  private:
    std::unique_ptr<Ui::CategoryWindow> ui;

    class CategoryFilterModel;
    std::unique_ptr<CategoryFilterModel> model_;
};
