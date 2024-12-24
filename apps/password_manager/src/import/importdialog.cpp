//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "importdialog.h"
#include "importrecordtablemodel.h"
#include "qkeysequence.h"
#include "qnamespace.h"
#include "ui_importdialog.h"
#include <QMenu>

ImportDialog::ImportDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::ImportDialog), model_{std::make_unique<ImportRecordTableModel>()},
      contextMenu_{std::make_unique<QMenu>(this)}, actionToggleApproval_{std::make_unique<QAction>(this)} {
    ui->setupUi(this);

    setupTableView();
    setupContextMenu();
}

ImportDialog::~ImportDialog() {
    delete ui;
}

void ImportDialog::setupTableView() {
    ui->tableView->setModel(model_.get());

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    auto header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(ImportRecordTableModel::COLUMN_TITLE, QHeaderView::Stretch);
    header->setSectionResizeMode(ImportRecordTableModel::COLUMN_UPDATED, QHeaderView::Stretch);
    header->setSectionResizeMode(ImportRecordTableModel::COLUMN_ACTION, QHeaderView::Stretch);
}

void ImportDialog::setupContextMenu() {
    actionToggleApproval_->setCheckable(true);
    actionToggleApproval_->setText(tr("Skip"));
    actionToggleApproval_->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    connect(actionToggleApproval_.get(), &QAction::toggled, this, &ImportDialog::onToggleApproval);

    this->addAction(actionToggleApproval_.get());
    contextMenu_->addAction(actionToggleApproval_.get());

    connect(contextMenu_.get(), &QMenu::aboutToShow, this, &ImportDialog::onContextMenuAboutToShow);
    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &ImportDialog::onContextMenuRequested);
}

void ImportDialog::setup(const std::vector<std::shared_ptr<ImportRecord>> &toImport) {
    model_->setItems(toImport);
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
