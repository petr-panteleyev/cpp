//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    std::unique_ptr<Ui::MainWindow> ui;
};
