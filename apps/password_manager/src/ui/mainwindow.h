/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardtableitemmodel.h"
#include "cardtablesortfiltermodel.h"
#include "fieldtableitemmodel.h"
#include "fieldtablesortfiltermodel.h"
#include <QAction>
#include <QItemSelection>
#include <QMainWindow>
#include <QMenu>

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
    void onCurrentCardChanged(const QModelIndex &current, const QModelIndex &previous);
    void onFieldTableDoubleClicked(const QModelIndex &index);
    void on_actionShow_Deleted_toggled(bool arg1);
    void on_actionExit_triggered();
    void fieldTableContextMenuRequested(QPoint pos);
    void onCopyField();
    void onOpenLink();

    void on_actionFilter_triggered();

    void on_searchField_textChanged(const QString &arg1);

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    CardTableItemModel       model_;
    CardTableSortFilterModel sortFilterModel_;

    FieldTableItemModel       fieldModel_;
    FieldTableSortFilterModel fieldFilterModel_;

    QAction copyFieldAction_;
    QAction openLinkAction_;
    QMenu   fieldContextMenu_;
};
#endif // MAINWINDOW_H
