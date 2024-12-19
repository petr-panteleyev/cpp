/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardeditdialog.h"
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

    // Actions and other events
    void onCopyField();
    void onOpenLink();
    void onEditMenuAboutToShow();
    void onToolsMenuAboutToShow();
    void onFieldTableDoubleClicked(const QModelIndex &index);
    void onFieldTableContextMenuRequested(QPoint pos);
    void onCurrentCardChanged(const QModelIndex &current, const QModelIndex &previous);
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onSearchFieldTextChanged(const QString &text);

    void onActionAbout();
    void onActionChangePassword();
    void onActionDelete();
    void onActionEdit();
    void onActionExit();
    void onActionFilter();
    void onActionFavorite();
    void onActionNew();
    void onActionNewCard();
    void onActionNewNote();
    void onActionOpen();
    void onActionPurge();
    void onActionRestore();
    void onActionShowDeletedToggled(bool checked);

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
    CardEditDialog       cardEditDialog_;
};
#endif // MAINWINDOW_H
