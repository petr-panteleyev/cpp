//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "importdialog.h"
#include "importrecordtablemodel.h"
#include "str.h"
#include "ui_importdialog.h"
#include <QMenu>

using std::make_unique;

ImportDialog::ImportDialog(QWidget *parent)
    : QDialog{parent}, ui{make_unique<Ui::ImportDialog>()}, model_{new ImportRecordTableModel{this}},
      contextMenu_{new QMenu{this}}, actionToggleApproval_{new QAction{Str::SKIP, this}} {
    ui->setupUi(this);

    setupTableView();
    setupContextMenu();
}

ImportDialog::~ImportDialog() {
}

void ImportDialog::setupTableView() {
    ui->tableView->setModel(model_);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    auto header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(ImportRecordTableModel::COLUMN_TITLE, QHeaderView::Stretch);
    header->setSectionResizeMode(ImportRecordTableModel::COLUMN_UPDATED, QHeaderView::Stretch);
    header->setSectionResizeMode(ImportRecordTableModel::COLUMN_ACTION, QHeaderView::Stretch);
}

void ImportDialog::setupContextMenu() {
    actionToggleApproval_->setCheckable(true);
    actionToggleApproval_->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    connect(actionToggleApproval_, &QAction::toggled, this, &ImportDialog::onToggleApproval);

    this->addAction(actionToggleApproval_);
    contextMenu_->addAction(actionToggleApproval_);

    connect(contextMenu_, &QMenu::aboutToShow, this, &ImportDialog::onContextMenuAboutToShow);
    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &ImportDialog::onContextMenuRequested);
}

void ImportDialog::setup(const std::vector<ImportRecord> &toImport) {
    model_->setRecords(toImport);
}

std::vector<ImportRecord> ImportDialog::records() const {
    return model_->records();
}

void ImportDialog::onContextMenuRequested(QPoint pos) {
    auto index = ui->tableView->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    contextMenu_->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void ImportDialog::onContextMenuAboutToShow() {
    auto currentIndex = ui->tableView->currentIndex();
    if (!currentIndex.isValid()) {
        return;
    }
    auto record = model_->at(currentIndex.row());
    actionToggleApproval_->setChecked(!record->approved());
}

void ImportDialog::onToggleApproval() {
    auto currentIndex = ui->tableView->currentIndex();
    if (!currentIndex.isValid()) {
        return;
    }
    model_->toggleApproval(currentIndex.row());
}
