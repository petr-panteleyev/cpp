/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "mainwindow.h"
#include "aboutdialog.h"
#include "aes256.h"
#include "card.h"
#include "cardeditdialog.h"
#include "exceptions.h"
#include "newcarddialog.h"
#include "newnotedialog.h"
#include "passworddialog.h"
#include "qthelpers.h"
#include "serializer.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDesktopServices>
#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidgetItem>

static constexpr int TAB_FIELDS = 0;
static constexpr int TAB_NOTE = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), copyFieldAction_{this}, openLinkAction_{tr("Open Link"), this},
      fieldContextMenu_{this} {
    ui->setupUi(this);

    sortFilterModel_.setSourceModel(&model_);
    ui->cardListView->setModel(&sortFilterModel_);

    sortFilterModel_.sort(0);

    auto header = ui->cardListView->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ui->cardListView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->cardListView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Field Table
    fieldFilterModel_.setSourceModel(&fieldModel_);
    ui->fieldTable->setModel(&fieldFilterModel_);

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
    QtHelpers::addActions(&fieldContextMenu_, {&copyFieldAction_, &openLinkAction_});

    auto selectionModel = ui->cardListView->selectionModel();
    connect(selectionModel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this,
            SLOT(onCurrentCardChanged(QModelIndex, QModelIndex)));
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSelectionChanged(QItemSelection, QItemSelection)));

    connect(ui->fieldTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onFieldTableDoubleClicked(QModelIndex)));
    connect(ui->fieldTable, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(fieldTableContextMenuRequested(QPoint)));

    connect(&copyFieldAction_, SIGNAL(triggered(bool)), this, SLOT(onCopyField()));
    connect(&openLinkAction_, SIGNAL(triggered(bool)), this, SLOT(onOpenLink()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    auto fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty()) {
        return;
    }

    PasswordDialog passwordDialog{this, fileName};
    passwordDialog.exec();
    auto password = passwordDialog.password();

    try {
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

                QByteArray decrypted;
                aes256::decrypt(data, password, decrypted);
                doc.setContent(decrypted);
            }
            file.close();

            std::vector<CardPtr> cards;
            Serializer::deserialize(doc, cards);
            model_.setItems(cards);

            if (model_.rowCount() > 0) {
                ui->cardListView->setCurrentIndex(sortFilterModel_.index(0, 0));
            }

            currentFileName_ = fileName;
        }
    } catch (const PasswordManagerException &ex) {
        QMessageBox::critical(this, tr("Critical Error"), ex.message());
    } catch (const aes256::DecryptionException &ex) {
        QMessageBox::critical(this, tr("Critical Error"), QString::fromStdString(ex.message()));
    }
}

void MainWindow::onCurrentCardChanged(const QModelIndex &current, const QModelIndex &previous) {
    if (!current.isValid()) {
        QtHelpers::enableActions(false, {ui->actionFavorite, ui->actionEdit, ui->actionDelete, ui->actionPurge});
    } else {
        auto sourceIndex = sortFilterModel_.mapToSource(current);
        auto currentCard = model_.cardAtIndex(sourceIndex.row());
        fieldModel_.setItems(currentCard->fields());

        if (currentCard->isNote()) {
            ui->tabWidget->setTabText(TAB_NOTE, currentCard->name());
        } else {
            ui->tabWidget->setTabText(TAB_FIELDS, currentCard->name());
            ui->tabWidget->setTabIcon(TAB_FIELDS, currentCard->picture().icon());
            ui->tabWidget->setTabText(TAB_NOTE, tr("Note"));
        }

        ui->tabWidget->setTabVisible(TAB_FIELDS, !currentCard->fields().empty());
        ui->tabWidget->setTabVisible(TAB_NOTE, !currentCard->note().isEmpty());

        ui->noteViewer->setText(currentCard->note());

        // Update actions
        QtHelpers::enableActions(true, {ui->actionFavorite, ui->actionEdit, ui->actionDelete, ui->actionPurge});

        ui->actionDelete->setText(currentCard->active() ? tr("Delete") : tr("Restore"));

        ui->actionPurge->setVisible(!currentCard->active());
        ui->actionFavorite->setChecked(currentCard->favorite());
    }
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
}

void MainWindow::on_actionShow_Deleted_toggled(bool checked) {
    sortFilterModel_.set_show_deleted(checked);

    auto selectionModel = ui->cardListView->selectionModel();
    ui->cardListView->scrollTo(selectionModel->currentIndex());
}

void MainWindow::on_actionExit_triggered() {
    close();
}

void MainWindow::onFieldTableDoubleClicked(const QModelIndex &index) {
    auto sourceIndex = fieldFilterModel_.mapToSource(index);
    auto field = fieldModel_.fieldAtIndex(sourceIndex.row());
    fieldModel_.toggleMasking(sourceIndex, field);
}

void MainWindow::fieldTableContextMenuRequested(QPoint pos) {
    auto index = ui->fieldTable->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    auto sourceIndex = fieldFilterModel_.mapToSource(index);
    auto field = fieldModel_.fieldAtIndex(sourceIndex.row());

    copyFieldAction_.setText(tr("Copy") + " \"" + field->name() + "\"");
    copyFieldAction_.setData(field->getValueAsString());
    openLinkAction_.setData(field->getValueAsString());
    fieldContextMenu_.popup(ui->fieldTable->viewport()->mapToGlobal(pos));

    openLinkAction_.setVisible(field->type() == FieldType::LINK);
}

void MainWindow::onCopyField() {
    auto fieldText = copyFieldAction_.data().toString();
    auto clipboard = QGuiApplication::clipboard();
    if (clipboard != nullptr) {
        clipboard->setText(fieldText);
    }
}

void MainWindow::onOpenLink() {
    auto urlText = openLinkAction_.data().toString();
    QDesktopServices::openUrl(QUrl(urlText));
}

void MainWindow::on_actionFilter_triggered() {
    ui->searchField->setFocus();
}

void MainWindow::on_searchField_textChanged(const QString &text) {
    sortFilterModel_.setFilterText(text);
}

void MainWindow::on_actionAbout_triggered() {
    AboutDialog aboutDialog{this};
    aboutDialog.exec();
}

void MainWindow::on_actionEdit_triggered() {
    auto selectionModel = ui->cardListView->selectionModel();
    auto currentIndex = selectionModel->currentIndex();
    if (!currentIndex.isValid()) {
        return;
    }

    auto sourceIndex = sortFilterModel_.mapToSource(currentIndex);
    auto currentCard = model_.cardAtIndex(sourceIndex.row());

    CardEditDialog dialog{*currentCard, this};
    auto           result = dialog.exec();
    if (result == QDialog::Accepted) {
        auto &updatedCard = dialog.card();
        model_.replace(sourceIndex, updatedCard);
        onCurrentCardChanged(currentIndex, currentIndex);
    }
}

void MainWindow::on_actionFavorite_triggered() {
    auto index = currentIndex();
    if (!index.isValid()) {
        return;
    }
    auto card = model_.cardAtIndex(index.row());
    card->toggleFavorite();
    model_.replace(index, *card);
    sortFilterModel_.invalidate();
    ui->cardListView->scrollTo(ui->cardListView->currentIndex());
}

const QModelIndex MainWindow::currentIndex() const noexcept {
    auto currentIndex = ui->cardListView->currentIndex();
    if (!currentIndex.isValid()) {
        return currentIndex;
    }

    return sortFilterModel_.mapToSource(currentIndex);
}

void MainWindow::on_actionNewCard_triggered() {
    NewCardDialog dialog{this};
    auto          result = dialog.exec();
    if (result == QDialog::Accepted) {
        model_.add(dialog.card());
    }
}

void MainWindow::on_actionNewNote_triggered() {
    NewNoteDialog dialog{this};
    auto          result = dialog.exec();
    if (result == QDialog::Accepted) {
        model_.add(dialog.note());
    }
}
