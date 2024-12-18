/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardtableitemmodel.h"
#include "cardtablesortfiltermodel.h"
#include "changepassworddialog.h"
#include "fieldtableitemmodel.h"
#include "fieldtablesortfiltermodel.h"
#include <QAction>
#include <QItemSelection>
#include <QMainWindow>
#include <QMenu>
#include <optional>

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
    const QModelIndex      currentIndex() const noexcept;
    std::optional<CardPtr> currentCard() const noexcept;
    void                   writeFile() const;

    void updateWindowTitle();
    void scrollToCurrentCard();

  private slots:
    void onCurrentCardChanged(const QModelIndex &current, const QModelIndex &previous);
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onFieldTableDoubleClicked(const QModelIndex &index);
    void fieldTableContextMenuRequested(QPoint pos);
    void onCopyField();
    void onOpenLink();
    void onEditMenuAboutToShow();
    void onToolsMenuAboutToShow();

    void on_actionOpen_triggered();
    void on_actionFilter_triggered();
    void on_searchField_textChanged(const QString &text);
    void on_actionAbout_triggered();
    void on_actionEdit_triggered();
    void on_actionFavorite_triggered();
    void on_actionNewCard_triggered();
    void on_actionNewNote_triggered();
    void on_actionNew_triggered();
    void on_actionChangePassword_triggered();
    void on_actionShow_Deleted_toggled(bool checked);
    void onActionExit();
    void on_actionDelete_triggered();
    void on_actionRestore_triggered();

    void on_actionPurge_triggered();

private:
    Ui::MainWindow *ui;

    CardTableItemModel       model_;
    CardTableSortFilterModel sortFilterModel_;

    FieldTableItemModel       fieldModel_;
    FieldTableSortFilterModel fieldFilterModel_;

    QAction copyFieldAction_;
    QAction openLinkAction_;
    QMenu   fieldContextMenu_;

    QString currentFileName_;
    QString currentPassword_;

    // Dialogs
    ChangePasswordDialog changePasswordDialog_;
};
#endif // MAINWINDOW_H
