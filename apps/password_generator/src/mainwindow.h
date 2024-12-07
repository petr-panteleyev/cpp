#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    void generate(const password_generator::PasswordGeneratorOptions &options);
    void visualize_options(const password_generator::PasswordGeneratorOptions &options);

  private slots:
    void on_actionGenerate_triggered();

    void on_actionExit_triggered();

    void on_actionUNIX_triggered();

    void on_actionPIN_triggered();

    void on_actionMedium_Password_triggered();

    void on_actionLong_Password_triggered();

    void on_actionCopy_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
