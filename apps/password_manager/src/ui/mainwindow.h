//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

  private:
    const QModelIndex currentIndex() const noexcept;
    std::optional<std::shared_ptr<Card>> currentCard() const noexcept;

    void writeFile() const { writeFile(currentFileName_, currentPassword_); }
    void writeFile(const QString &fileName, const QString &password) const;

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

    void onPasswordDialogAccepted();
    void continueOpen(const QString &fileName, const QString &password);
    void continueImport(const QString &fileName, const QString &password);

    void onActionAbout();
    void onActionChangePassword();
    void onActionDelete();
    void onActionEdit();
    void onActionExit();
    void onActionExport();
    void onActionFilter();
    void onActionFavorite();
    void onActionImport();
    void onActionNew();
    void onActionNewCard();
    void onActionNewNote();
    void onActionOpen();
    void onActionPurge();
    void onActionRestore();
    void onActionSettings();
    void onActionShowDeletedToggled(bool checked);

  private:
    static void loadRecords(const QString &fileName, const QString &password,
                            std::vector<std::shared_ptr<Card>> &result);

  private:
    std::unique_ptr<Ui::MainWindow> ui;

    std::unique_ptr<CardTableItemModel> cardModel_;
    std::unique_ptr<CardTableSortFilterModel> sortFilterModel_;

    std::unique_ptr<FieldTableItemModel> fieldModel_;
    std::unique_ptr<FieldTableSortFilterModel> fieldFilterModel_;

    QAction copyFieldAction_;
    QAction openLinkAction_;
    std::unique_ptr<QMenu> fieldContextMenu_;

    QString currentFileName_;
    QString currentPassword_;

    // Dialogs
    std::unique_ptr<PasswordDialog> passwordDialog_;
    std::unique_ptr<ChangePasswordDialog> changePasswordDialog_;
    std::unique_ptr<CardEditDialog> cardEditDialog_;
    std::unique_ptr<ImportDialog> importDialog_;
    std::unique_ptr<SettingsDialog> settingsDialog_;
};
#endif // MAINWINDOW_H
