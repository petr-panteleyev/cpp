/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelection>
#include <QMainWindow>
#include "cardtableitemmodel.h"
#include "cardtablesortfiltermodel.h"

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

  private slots:
    void on_actionOpen_triggered();
    void on_item_selected(const QItemSelection &selected, const QItemSelection &deselected);
    void on_current_changed(const QModelIndex &current, const QModelIndex &previous);

    void on_actionShow_Deleted_toggled(bool arg1);

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    CardTableItemModel model_;
    CardTableSortFilterModel sort_filter_model_;
};
#endif // MAINWINDOW_H
