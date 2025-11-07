//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "generator.hpp"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    static constexpr std::array<int, 10> PASSWORD_LENGTH_OPTIONS = {4, 6, 8, 16, 24, 32, 40, 48, 56, 64};
    static constexpr int DEFAULT_LENGTH_INDEX = 3;

  private:
    void visualizeOptions(const pwdgen::PasswordGeneratorOptions &options);
    void generate(const pwdgen::PasswordGeneratorOptions &options);

  private:
    std::unique_ptr<Ui::MainWindow> ui;
};
