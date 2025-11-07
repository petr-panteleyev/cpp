//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "observablevalue.hpp"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Card;
class CardEditDialog;
class CardTableItemModel;
class CardTableSortFilterModel;
class ChangePasswordDialog;
class FieldTableItemModel;
class FieldTableSortFilterModel;
class ImportDialog;
class PasswordDialog;
class QItemSelection;
class QMenu;
class SettingsDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;

  private:
    const QModelIndex currentIndex() const noexcept;

    void writeFile() const;
    void writeFile(const QString &fileName, const QString &password) const;

    void updateWindowTitle();
    void scrollToCurrentCard();

    void setupCardContextMenu();

    // Actions and other events
    void onCopyField();
    void onOpenLink();
    void updateActionsState();
    void onFieldTableDoubleClicked(const QModelIndex &index);
    void onFieldTableContextMenuRequested(QPoint pos);
    void onCurrentCardChanged(const QModelIndex &current, const QModelIndex &previous);
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onSearchFieldTextChanged(const QString &text);

    void onPasswordDialogAccepted();
    void continueOpen(const QString &fileName, const QString &password);
    void continueImport(const QString &fileName, const QString &password);

    void updateFonts();

    void onActionChangePassword();
    void onActionDelete();
    void onActionEdit();
    void onActionExport();
    void onActionFavorite();
    void onActionImport();
    void onActionNew();
    void onActionNewCard();
    void onActionNewNote();
    void onActionOpen();
    void onActionPurge();
    void onActionRestore();
    void onActionShowDeletedToggled(bool checked);

  private:
    static std::vector<Card> loadRecords(const QString &fileName, const QString &password);

  private:
    std::unique_ptr<Ui::MainWindow> ui;

    CardTableItemModel *cardModel_;
    CardTableSortFilterModel *sortFilterModel_;
    QMenu *cardContextMenu_;

    FieldTableItemModel *fieldModel_;
    FieldTableSortFilterModel *fieldFilterModel_;

    QAction *copyFieldAction_;
    QAction *openLinkAction_;
    QMenu *fieldContextMenu_;

    Common::ObservableValue<QString> currentFileName_;
    QString currentPassword_;

    // Dialogs
    PasswordDialog *passwordDialog_;
    ChangePasswordDialog *changePasswordDialog_;
    CardEditDialog *cardEditDialog_;
    ImportDialog *importDialog_;
    SettingsDialog *settingsDialog_;
};
