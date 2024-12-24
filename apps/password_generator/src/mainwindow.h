/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "generator.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    void generate(const pwdgen::PasswordGeneratorOptions &options);
    void visualizeOptions(const pwdgen::PasswordGeneratorOptions &options);

    // actions
    void onActionGenerate();
    void onActionExit();
    void onActionUnix();
    void onActionPin();
    void onActionMediumPassword();
    void onActionLongPassword();
    void onActionCopy();

  private:
    std::unique_ptr<Ui::MainWindow> ui;
};
#endif // MAINWINDOW_H
