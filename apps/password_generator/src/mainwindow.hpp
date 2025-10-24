//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace pwdgen {
class PasswordGeneratorOptions;
} // namespace pwdgen

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    void generate(const pwdgen::PasswordGeneratorOptions &options);
    void visualizeOptions(const pwdgen::PasswordGeneratorOptions &options);

  private:
    std::unique_ptr<Ui::MainWindow> ui;
};
