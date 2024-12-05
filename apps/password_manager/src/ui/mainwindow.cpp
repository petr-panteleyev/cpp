/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "mainwindow.h"
#include "../model/card.h"
#include "../serializer.h"
#include <./ui_mainwindow.h>
#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    sort_filter_model_.setSourceModel(&model_);
    ui->cardListView->setModel(&sort_filter_model_);

    auto header = ui->cardListView->horizontalHeader();
    assert(header != nullptr);

    ui->cardListView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->cardListView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->cardListView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->cardListView->setSelectionMode(QAbstractItemView::SingleSelection);

    //    auto selectionModel = ui->cardListView->selectionModel();
    //    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
    //            SLOT(on_item_selected(QItemSelection, QItemSelection)));
    //    connect(selectionModel, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this,
    //            SLOT(on_current_changed(QModelIndex, QModelIndex)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    auto fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty()) {
        return;
    }

    QFile file{fileName};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("File cannot be opened!");
    } else {
        QDomDocument doc;
        doc.setContent(&file);
        file.close();

        std::vector<CardPtr> cards;
        Serializer::deserialize(doc, cards);
        model_.setItems(cards);
        sort_filter_model_.sort(0);
    }
}

void MainWindow::on_item_selected(const QItemSelection &selected, const QItemSelection &deselected) {
}

void MainWindow::on_current_changed(const QModelIndex &current, const QModelIndex &previous) {
}

void MainWindow::on_actionShow_Deleted_toggled(bool checked) {
    sort_filter_model_.set_show_deleted(checked);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

