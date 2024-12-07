/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "mainwindow.h"
#include "aes256.h"
#include "card.h"
#include "serializer.h"
#include <./ui_mainwindow.h>
#include <QClipboard>
#include <QDesktopServices>
#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QTableWidgetItem>

static constexpr int TAB_FIELDS = 0;
static constexpr int TAB_NOTE = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), copyFieldAction_{this}, openLinkAction_{tr("Open Link"), this},
      fieldContextMenu_{this} {
    ui->setupUi(this);

    sortFilterModel_.setSourceModel(&model_);
    ui->cardListView->setModel(&sortFilterModel_);

    auto header = ui->cardListView->horizontalHeader();
    assert(header != nullptr);

    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ui->cardListView->setSelectionMode(QAbstractItemView::SingleSelection);

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
    fieldContextMenu_.addAction(&copyFieldAction_);
    fieldContextMenu_.addAction(&openLinkAction_);

    auto selectionModel = ui->cardListView->selectionModel();
    connect(selectionModel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this,
            SLOT(onCurrentCardChanged(QModelIndex, QModelIndex)));

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

    bool ok;
    auto password = QInputDialog::getText(this, "Password", "Master Password", QLineEdit::Password, "", &ok);
    if (!ok) {
        return;
    }

    QFile file{fileName};
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("File cannot be opened!");
    } else {
        QDomDocument doc;

        if (password.isEmpty()) {
            doc.setContent(&file);
        } else {
            auto data = file.readAll();
            auto decrypted = aes256::decrypt(data, password.toStdString());
            doc.setContent(QByteArray::fromRawData((const char *)decrypted.first.get(), decrypted.second));
        }
        file.close();

        std::vector<CardPtr> cards;
        Serializer::deserialize(doc, cards);
        model_.setItems(cards);
        sortFilterModel_.sort(0);
    }
}

void MainWindow::onCurrentCardChanged(const QModelIndex &current, const QModelIndex &previous) {
    auto sourceIndex = sortFilterModel_.mapToSource(current);
    auto currentCard = model_.cardAtIndex(sourceIndex.row());
    fieldModel_.setItems(currentCard->fields());

    if (currentCard->cardClass() == CardClass::NOTE) {
        ui->tabWidget->setTabText(TAB_NOTE, currentCard->name());
    } else {
        ui->tabWidget->setTabText(TAB_FIELDS, currentCard->name());
        ui->tabWidget->setTabIcon(TAB_FIELDS, currentCard->picture().icon());
        ui->tabWidget->setTabText(TAB_NOTE, tr("Note"));
    }

    ui->tabWidget->setTabVisible(TAB_FIELDS, !currentCard->fields().empty());
    ui->tabWidget->setTabVisible(TAB_NOTE, !currentCard->note().isEmpty());

    ui->noteViewer->setText(currentCard->note());
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
