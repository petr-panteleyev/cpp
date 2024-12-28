//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "mainwindow.h"
#include "aes256.h"
#include "card.h"
#include "cardeditdialog.h"
#include "cardtableitemmodel.h"
#include "cardtablesortfiltermodel.h"
#include "changepassworddialog.h"
#include "cryptoexception.h"
#include "exceptions.h"
#include "field.h"
#include "fieldtableitemmodel.h"
#include "fieldtablesortfiltermodel.h"
#include "fieldtype.h"
#include "fonttype.h"
#include "importdialog.h"
#include "importutil.h"
#include "newcarddialog.h"
#include "newnotedialog.h"
#include "passworddialog.h"
#include "qmainwindow.h"
#include "qthelpers.h"
#include "serializer.h"
#include "settings.h"
#include "settingsdialog.h"
#include "ui_mainwindow.h"
#include "version.h"
#include <QClipboard>
#include <QDesktopServices>
#include <QDomDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <memory>

using namespace Crypto;

constexpr int TAB_FIELDS = 0;
constexpr int TAB_NOTE = 1;

static const QString FILE_FILTERS{QApplication::translate("MainWindow", "Password Files (*.pwd);;All Files (*.*)")};

static const QString ABOUT_TEXT = R"(
<h1>Password Manager</h1>
<table border='0'>
<tr><td>Version:<td>%1
<tr><td>Build Date:<td>%2
</table>
Copyright &copy; 2024 Petr Panteleyev
)";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui{std::make_unique<Ui::MainWindow>()}, cardModel_{new CardTableItemModel{this}},
      sortFilterModel_{new CardTableSortFilterModel{this}}, fieldModel_{new FieldTableItemModel{this}},
      fieldFilterModel_{new FieldTableSortFilterModel{this}}, copyFieldAction_{new QAction{this}},
      openLinkAction_{new QAction{tr("Open Link"), this}}, fieldContextMenu_{new QMenu{this}}, currentFileName_{""},
      passwordDialog_{new PasswordDialog{this}}, changePasswordDialog_{new ChangePasswordDialog{this}},
      cardEditDialog_{new CardEditDialog{this}}, importDialog_{new ImportDialog{this}},
      settingsDialog_{new SettingsDialog{this}} {
    ui->setupUi(this);

    sortFilterModel_->setSourceModel(cardModel_);
    ui->cardListView->setModel(sortFilterModel_);

    sortFilterModel_->sort(0);

    auto header = ui->cardListView->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ui->cardListView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->cardListView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Field Table
    fieldFilterModel_->setSourceModel(fieldModel_);
    ui->fieldTable->setModel(fieldFilterModel_);
    ui->fieldTable->setStyleSheet("QTableView::item { border:0px; padding: 3px; }");

    auto fieldTableHeader = ui->fieldTable->horizontalHeader();
    assert(fieldTableHeader != nullptr);
    fieldTableHeader->setSectionResizeMode(0, QHeaderView::Stretch);
    fieldTableHeader->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->fieldTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->fieldTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->fieldTable->setFocusPolicy(Qt::NoFocus);

    // TabWidget
    ui->tabWidget->setTabText(TAB_FIELDS, "");
    ui->tabWidget->setTabIcon(TAB_FIELDS, Picture::GENERIC.icon());
    ui->tabWidget->setTabText(TAB_NOTE, tr("Note"));
    ui->tabWidget->setTabIcon(TAB_NOTE, Picture::NOTE.icon());

    // Field context menu
    QtHelpers::addActions(fieldContextMenu_, {copyFieldAction_, openLinkAction_});

    auto selectionModel = ui->cardListView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::onCurrentCardChanged);
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::onSelectionChanged);

    connect(ui->fieldTable, &QTableView::doubleClicked, this, &MainWindow::onFieldTableDoubleClicked);
    connect(ui->fieldTable, &QTableView::customContextMenuRequested, this,
            &MainWindow::onFieldTableContextMenuRequested);

    connect(ui->searchField, &QLineEdit::textChanged, this, &MainWindow::onSearchFieldTextChanged);

    connect(ui->actionExit, &QAction::triggered, [this]() { close(); });
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpen);
    connect(ui->actionFilter, &QAction::triggered, this, &MainWindow::onActionFilter);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onActionAbout);
    connect(ui->actionFavorite, &QAction::triggered, this, &MainWindow::onActionFavorite);
    connect(ui->actionNewCard, &QAction::triggered, this, &MainWindow::onActionNewCard);
    connect(ui->actionNewNote, &QAction::triggered, this, &MainWindow::onActionNewNote);
    connect(ui->actionChangePassword, &QAction::triggered, this, &MainWindow::onActionChangePassword);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onActionDelete);
    connect(ui->actionRestore, &QAction::triggered, this, &MainWindow::onActionRestore);
    connect(ui->actionPurge, &QAction::triggered, this, &MainWindow::onActionPurge);
    connect(ui->actionShow_Deleted, &QAction::toggled, this, &MainWindow::onActionShowDeletedToggled);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->actionExport, &QAction::triggered, this, &MainWindow::onActionExport);
    connect(ui->actionImport, &QAction::triggered, this, &MainWindow::onActionImport);
    connect(ui->actionSettings, &QAction::triggered, [this]() { settingsDialog_->show(); });

    connect(copyFieldAction_, &QAction::triggered, this, &MainWindow::onCopyField);
    connect(openLinkAction_, &QAction::triggered, this, &MainWindow::onOpenLink);

    connect(ui->menuEdit, &QMenu::aboutToShow, this, &MainWindow::onEditMenuAboutToShow);

    connect(passwordDialog_, &QDialog::accepted, this, &MainWindow::onPasswordDialogAccepted);
    connect(settingsDialog_, &QDialog::accepted, [this]() { updateFonts(); });

    currentFileName_.subscribe([this](const QString &, const QString &newValue) {
        QtHelpers::enableActions(!newValue.isEmpty(), {ui->actionNewCard, ui->actionNewNote, ui->actionImport,
                                                       ui->actionExport, ui->actionChangePassword, ui->actionPurge});
        updateWindowTitle();
    });

    updateFonts();
}

MainWindow::~MainWindow() {
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    auto fileName = Settings::getCurrentFile();
    if (fileName.isEmpty()) {
        return;
    }

    QTimer::singleShot(10, [fileName, this]() {
        passwordDialog_->setFileName(fileName);
        passwordDialog_->show(PasswordDialog::Mode::OPEN);
    });
}

void MainWindow::onPasswordDialogAccepted() {
    auto fileName = passwordDialog_->getFileName();
    auto password = passwordDialog_->getPassword();

    if (passwordDialog_->getMode() == PasswordDialog::Mode::OPEN) {
        continueOpen(fileName, password);
    } else {
        continueImport(fileName, password);
    }
}

void MainWindow::continueOpen(const QString &fileName, const QString &password) {
    try {
        auto cards = loadRecords(fileName, password);

        cardModel_->setItems(cards);
        if (cardModel_->rowCount() > 0) {
            ui->cardListView->setCurrentIndex(sortFilterModel_->index(0, 0));
        }

        currentFileName_ = fileName;
        currentPassword_ = password;

        Settings::setCurrentFile(currentFileName_.get());
    } catch (const PasswordManagerException &ex) {
        QMessageBox::critical(this, tr("Critical Error"), ex.message());
    } catch (const CryptoException &ex) {
        QMessageBox::critical(this, tr("Critical Error"), QString::fromStdString(ex.message()));
    }
}

void MainWindow::onActionOpen() {
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open"), QString(), FILE_FILTERS);
    if (fileName.isEmpty()) {
        return;
    }

    passwordDialog_->setFileName(fileName);
    passwordDialog_->show(PasswordDialog::Mode::OPEN);
}

void MainWindow::onCurrentCardChanged(const QModelIndex &current, const QModelIndex &previous) {
    if (current.isValid()) {
        auto sourceIndex = sortFilterModel_->mapToSource(current);
        auto currentCard = cardModel_->cardAtIndex(sourceIndex.row());
        fieldModel_->setItems(currentCard->fields());

        if (currentCard->isNote()) {
            ui->tabWidget->setTabText(TAB_NOTE, currentCard->name());
        } else {
            ui->tabWidget->setTabText(TAB_FIELDS, currentCard->name());
            ui->tabWidget->setTabIcon(TAB_FIELDS, currentCard->picture().icon());
            ui->tabWidget->setTabText(TAB_NOTE, tr("Note"));
        }

        ui->tabWidget->setTabVisible(TAB_FIELDS, !currentCard->fields().empty());
        ui->tabWidget->setTabVisible(TAB_NOTE, currentCard->isNote() || !currentCard->note().isEmpty());

        ui->noteViewer->setText(currentCard->note());
    } else {
        fieldModel_->setItems({});
        ui->noteViewer->setText("");
        ui->tabWidget->setTabText(TAB_FIELDS, "");
        ui->tabWidget->setTabIcon(TAB_FIELDS, Picture::GENERIC.icon());
        ui->tabWidget->setTabVisible(TAB_FIELDS, true);
        ui->tabWidget->setTabVisible(TAB_NOTE, false);
    }

    onEditMenuAboutToShow();
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    if (selected.indexes().isEmpty()) {
        ui->cardListView->setCurrentIndex(QModelIndex());
    }
}

void MainWindow::onActionShowDeletedToggled(bool checked) {
    sortFilterModel_->setShowDeleted(checked);
    scrollToCurrentCard();
}

void MainWindow::onFieldTableDoubleClicked(const QModelIndex &index) {
    auto sourceIndex = fieldFilterModel_->mapToSource(index);
    auto field = fieldModel_->fieldAtIndex(sourceIndex.row());

    if (field->type() == FieldType::LINK && Settings::getOpenLinkWithDoubleClick()) {
        QDesktopServices::openUrl(QUrl(field->getValueAsString()));
    } else {
        fieldModel_->toggleMasking(sourceIndex, field);
    }
}

void MainWindow::onFieldTableContextMenuRequested(QPoint pos) {
    auto index = ui->fieldTable->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    auto sourceIndex = fieldFilterModel_->mapToSource(index);
    auto field = fieldModel_->fieldAtIndex(sourceIndex.row());

    copyFieldAction_->setText(tr("Copy") + " \"" + field->name() + "\"");
    copyFieldAction_->setData(field->getValueAsString());
    openLinkAction_->setData(field->getValueAsString());
    fieldContextMenu_->popup(ui->fieldTable->viewport()->mapToGlobal(pos));

    openLinkAction_->setVisible(field->type() == FieldType::LINK);
}

void MainWindow::onCopyField() {
    auto fieldText = copyFieldAction_->data().toString();
    auto clipboard = QGuiApplication::clipboard();
    if (clipboard != nullptr) {
        clipboard->setText(fieldText);
    }
}

void MainWindow::onOpenLink() {
    auto urlText = openLinkAction_->data().toString();
    QDesktopServices::openUrl(QUrl(urlText));
}

void MainWindow::onActionFilter() {
    ui->searchField->setFocus();
}

void MainWindow::onSearchFieldTextChanged(const QString &text) {
    sortFilterModel_->setFilterText(text);
}

void MainWindow::onActionAbout() {
    auto text = QString(ABOUT_TEXT)
                    .arg(QString::fromStdString(Version::projectVersion))
                    .arg(QString::fromStdString(Version::buildDate));
    QMessageBox::about(this, tr("About"), text);
}

void MainWindow::onActionEdit() {
    auto currentIndex = ui->cardListView->selectionModel()->currentIndex();
    if (!currentIndex.isValid()) {
        return;
    }
    auto sourceIndex = sortFilterModel_->mapToSource(currentIndex);
    auto currentCard = cardModel_->cardAtIndex(sourceIndex.row());

    cardEditDialog_->setCard(*currentCard);

    if (cardEditDialog_->exec() == QDialog::Accepted) {
        auto &updatedCard = cardEditDialog_->card();
        cardModel_->replace(sourceIndex.row(), updatedCard);
        onCurrentCardChanged(currentIndex, currentIndex);
        writeFile();
    }
}

void MainWindow::onActionFavorite() {
    auto index = currentIndex();
    if (!index.isValid()) {
        return;
    }
    auto card = this->cardModel_->cardAtIndex(index.row());
    card->toggleFavorite();
    this->cardModel_->replace(index.row(), card);
    this->sortFilterModel_->invalidate();
    scrollToCurrentCard();
    writeFile();
}

const QModelIndex MainWindow::currentIndex() const noexcept {
    auto currentIndex = ui->cardListView->selectionModel()->currentIndex();
    if (!currentIndex.isValid()) {
        return currentIndex;
    }

    return this->sortFilterModel_->mapToSource(currentIndex);
}

std::optional<std::shared_ptr<Card>> MainWindow::currentCard() const noexcept {
    auto index = currentIndex();
    if (!index.isValid()) {
        return std::nullopt;
    }
    return std::optional(this->cardModel_->cardAtIndex(index.row()));
}

void MainWindow::onActionNewCard() {
    NewCardDialog dialog{this};
    auto result = dialog.exec();
    if (result == QDialog::Accepted) {
        cardModel_->add(dialog.card());
        writeFile();
    }
}

void MainWindow::onActionNewNote() {
    NewNoteDialog dialog{this};
    auto result = dialog.exec();
    if (result == QDialog::Accepted) {
        cardModel_->add(dialog.note());
        writeFile();
    }
}

void MainWindow::writeFile(const QString &fileName, const QString &password) const {
    if (fileName.isEmpty()) {
        return;
    }

    QByteArray buffer;
    Serializer::serialize(cardModel_->data(), buffer);

    QFile file{fileName};
    if (!file.open(QIODevice::WriteOnly)) {
        throw PasswordManagerException("File cannot be saved!");
    }

    if (!password.isEmpty()) {
        auto encrypted = aes256::encrypt(buffer, password.toStdString());
        file.write(encrypted.data(), encrypted.size());
    } else {
        file.write(buffer);
    }

    file.close();
}

void MainWindow::onActionNew() {
    auto fileName = QFileDialog::getSaveFileName(this, tr("New File"), QString(), FILE_FILTERS);
    if (fileName.isEmpty()) {
        return;
    }

    changePasswordDialog_->reset(fileName);
    if (changePasswordDialog_->exec() != QDialog::Accepted) {
        return;
    }

    auto password = changePasswordDialog_->password();

    currentFileName_ = fileName;
    currentPassword_ = password;

    cardModel_->setItems({});
    writeFile();
}

void MainWindow::onEditMenuAboutToShow() {
    bool hasCurrentCard = false;
    auto index = currentIndex();
    if (index.isValid()) {
        hasCurrentCard = true;
    }

    QtHelpers::enableActions(hasCurrentCard, {ui->actionEdit, ui->actionFavorite, ui->actionDelete});

    if (hasCurrentCard) {
        auto card = this->cardModel_->cardAtIndex(index.row());
        ui->actionRestore->setVisible(!card->active());
        ui->actionRestore->setEnabled(!card->active());
        ui->actionDelete->setText(card->active() ? tr("Delete") : tr("Finally Delete"));
        ui->actionFavorite->setChecked(card->favorite());
    }
}

void MainWindow::updateWindowTitle() {
    auto title = tr("Password Manager");
    if (currentFileName_.get().isEmpty()) {
        setWindowTitle(title);
    } else {
        setWindowTitle(title + " - " + currentFileName_.get());
    }
}

void MainWindow::onActionChangePassword() {
    changePasswordDialog_->reset(currentFileName_.get());
    if (changePasswordDialog_->exec() != QDialog::Accepted) {
        return;
    }
    currentPassword_ = changePasswordDialog_->password();
    writeFile();
}

void MainWindow::onActionDelete() {
    auto index = currentIndex();
    if (!index.isValid()) {
        return;
    }
    auto card = cardModel_->cardAtIndex(index.row());

    if (card->active()) {
        auto result = QMessageBox::question(this, tr("Delete"), tr("Are you sure to delete ") + card->name() + "?");
        if (result != QMessageBox::Yes) {
            return;
        }
        card->toggleActive();
        cardModel_->replace(index.row(), card);
    } else {
        auto result = QMessageBox::question(this, tr("Finally Delete"),
                                            tr("Are you sure to finally delete ") + card->name() + "?");
        if (result != QMessageBox::Yes) {
            return;
        }
        cardModel_->deleteCard(index.row());
    }

    sortFilterModel_->invalidate();
    scrollToCurrentCard();
    writeFile();
}

void MainWindow::scrollToCurrentCard() {
    ui->cardListView->scrollTo(ui->cardListView->currentIndex());
}

void MainWindow::onActionRestore() {
    auto index = currentIndex();
    if (!index.isValid()) {
        return;
    }
    auto card = this->cardModel_->cardAtIndex(index.row());

    if (card->active()) {
        return;
    }

    card->toggleActive();
    cardModel_->replace(index.row(), card);
    sortFilterModel_->invalidate();
    scrollToCurrentCard();
    writeFile();
}

void MainWindow::onActionPurge() {
    auto result = QMessageBox::question(this, tr("Purge"), tr("Are you sure to purge all deleted items?"));
    if (result != QMessageBox::Yes) {
        return;
    }
    cardModel_->purgeInactive();
    sortFilterModel_->invalidate();
    scrollToCurrentCard();
    writeFile();
}

void MainWindow::onActionExport() {
    auto fileName = QFileDialog::getSaveFileName(this, tr("Export"), QString(), FILE_FILTERS);
    if (fileName.isEmpty()) {
        return;
    }
    changePasswordDialog_->reset(fileName);
    if (changePasswordDialog_->exec() != QDialog::Accepted) {
        return;
    }
    auto password = changePasswordDialog_->password();
    writeFile(fileName, password);
}

void MainWindow::onActionImport() {
    auto fileName = QFileDialog::getOpenFileName(this, tr("Import"), QString(), FILE_FILTERS);
    if (fileName.isEmpty()) {
        return;
    }
    passwordDialog_->setFileName(fileName);
    passwordDialog_->show(PasswordDialog::Mode::IMPORT);
}

void MainWindow::continueImport(const QString &fileName, const QString &password) {
    try {
        auto toImport = loadRecords(fileName, password);

        auto importRecords = ImportUtil::calculateImport(cardModel_->data(), toImport);
        if (importRecords.empty()) {
            QMessageBox::information(this, tr("Import"), tr("No cards to import"));
        } else {
            importDialog_->setup(importRecords);
            if (importDialog_->exec() == QDialog::Accepted) {
                auto view = importRecords | std::views::filter([](const auto &rec) { return rec->approved(); }) |
                            std::views::transform([](const auto &rec) { return rec->cardToImport(); });

                if (!view.empty()) {
                    for (const auto &c : view) {
                        cardModel_->addOrReplace(c);
                    }
                    writeFile();
                }
            }
        }
    } catch (const PasswordManagerException &ex) {
        QMessageBox::critical(this, tr("Critical Error"), ex.message());
    } catch (const CryptoException &ex) {
        QMessageBox::critical(this, tr("Critical Error"), QString::fromStdString(ex.message()));
    }
}

std::vector<std::shared_ptr<Card>> MainWindow::loadRecords(const QString &fileName, const QString &password) {
    QFile file{fileName};
    if (!file.open(QIODevice::ReadOnly)) {
        throw PasswordManagerException("File cannot be opened!");
    } else {
        QDomDocument doc;

        if (password.isEmpty()) {
            bool success = doc.setContent(&file);
            if (!success) {
                throw PasswordManagerException("File cannot be parsed!");
            }
        } else {
            auto data = file.readAll();
            auto decrypted = aes256::decrypt(data, password.toStdString());
            doc.setContent(QByteArray::fromRawData(decrypted.data(), decrypted.size()));
        }
        file.close();

        std::vector<std::shared_ptr<Card>> result;
        Serializer::deserialize(doc, result);
        return result;
    }
}

void MainWindow::updateFonts() {
    auto textFont = Settings::getFont(Settings::FontType::TEXT);
    ui->cardListView->setFont(textFont);
    ui->fieldTable->setFont(textFont);

    auto menuFont = Settings::getFont(Settings::FontType::MENU);

    ui->menubar->setFont(menuFont);
    for (auto a : ui->menubar->actions()) {
        auto menu = a->menu();
        if (menu != nullptr) {
            menu->setFont(menuFont);
        }
    }
}
