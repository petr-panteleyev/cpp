/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "cardeditdialog.h"
#include "fieldvalueeditdelegate.h"
#include "picture.h"
#include "qthelpers.h"
#include "ui_cardeditdialog.h"
#include <QAbstractScrollArea>
#include <QValidator>
#include <QMessageBox>

class NotEmptyValidator : public QValidator {
  public:
    virtual QValidator::State validate(QString &input, int &pos) const override {
        return input.isEmpty() ? QValidator::State::Invalid : QValidator::State::Acceptable;
    }
};

CardEditDialog::CardEditDialog(const Card &card, QWidget *parent)
    : QDialog(parent), ui(new Ui::CardEditDialog), card_{card}, fieldTableModel_{this},
      fieldAddAction_{tr("Add"), this}, fieldDeleteAction_{tr("Delete"), this}, fieldUpAction_{tr("Up"), this},
      fieldDownAction_{tr("Down"), this}, fieldGenerateAction_(tr("Generate"), this)

{
    ui->setupUi(this);

    fieldTableModel_.setFields(card.fields());

    setupFieldTable();
    setupFieldTableContextMenu();

    ui->notesEditor->appendPlainText(card.note());
    ui->nameEditor->setText(card.name());
    ui->nameEditor->setValidator(new NotEmptyValidator());

    initPictureComboBox();

    // Fields and picture are editable for CARD only
    bool isCard = card.isCard();
    ui->tabWidget->setTabVisible(0, isCard);
    ui->pictureComboBox->setVisible(isCard);
    ui->pictureLabel->setVisible(isCard);
}

CardEditDialog::~CardEditDialog() {
    delete ui;
}

void CardEditDialog::setupFieldTable() {
    QTableView *t = ui->fieldsTable;

    QtHelpers::addActions(
        t, {&fieldAddAction_, &fieldDeleteAction_, &fieldGenerateAction_, &fieldUpAction_, &fieldDownAction_});

    t->setModel(&fieldTableModel_);
    t->setEditTriggers(QAbstractItemView::DoubleClicked);
    t->setItemDelegateForColumn(EditFieldListModel::FIELD_TABLE_TYPE_COLUMN, new FieldValueEditDelegate());
    t->setItemDelegateForColumn(EditFieldListModel::FIELD_TABLE_VALUE_COLUMN, new FieldValueEditDelegate());

    connect(t->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this,
            SLOT(fieldTableCurrentRowChanged(QModelIndex, QModelIndex)));

    auto header = t->horizontalHeader();
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_NAME_COLUMN, QHeaderView::Stretch);
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_TYPE_COLUMN, QHeaderView::Stretch);
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_VALUE_COLUMN, QHeaderView::Stretch);
}

void CardEditDialog::setupFieldTableContextMenu() {
    fieldAddAction_.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    fieldDeleteAction_.setShortcut(QKeySequence(Qt::Key_Delete));
    fieldGenerateAction_.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));
    fieldUpAction_.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Up));
    fieldDownAction_.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Down));

    QtHelpers::addActions(&fieldTableContextMenu_,
                          {&fieldAddAction_, &fieldDeleteAction_, nullptr, &fieldGenerateAction_, nullptr,
                           &fieldUpAction_, &fieldDownAction_});

    connect(&fieldAddAction_, SIGNAL(triggered(bool)), this, SLOT(onAddField()));
    connect(&fieldDeleteAction_, SIGNAL(triggered(bool)), this, SLOT(onDeleteField()));
    connect(&fieldUpAction_, SIGNAL(triggered(bool)), this, SLOT(onFieldUp()));
    connect(&fieldDownAction_, SIGNAL(triggered(bool)), this, SLOT(onFieldDown()));

    connect(ui->fieldsTable, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(fieldTableContextMenuRequested(QPoint)));
}

// TODO: do some validation here
void CardEditDialog::done(int code) {
    if (code == QDialog::Accepted) {
        auto newName = ui->nameEditor->text();
        if (newName.isEmpty()) {
            return;
        }

        card_.setName(newName);
        card_.setFields(fieldTableModel_.fields());
        // picture
        auto pictureOrdinal = ui->pictureComboBox->currentData().toUInt();
        card_.setPicture(Picture::valueOf(pictureOrdinal));
        // note
        card_.setNote(ui->notesEditor->toPlainText());
    }
    QDialog::done(code);
}

void CardEditDialog::initPictureComboBox() {
    auto index = 0;
    for (const Picture &picture : Picture::values()) {
        ui->pictureComboBox->addItem(picture.icon(), "", picture.ordinal());
        if (card_.picture() == picture) {
            ui->pictureComboBox->setCurrentIndex(index);
        }
        ++index;
    }
}

void CardEditDialog::onAddField() {
    fieldTableModel_.addField();
}

void CardEditDialog::onDeleteField() {
    auto index = ui->fieldsTable->currentIndex();
    if (!index.isValid()) {
        return;
    }
    auto field = fieldTableModel_.at(index.row());

    auto result = QMessageBox::question(this, tr("Delete"), tr("Are you sure to delete ") + field->name() + "?");
    if (result != QMessageBox::Yes) {
        return;
    }

    fieldTableModel_.deleteField(index.row());
}

void CardEditDialog::onFieldUp() {
    auto index = ui->fieldsTable->currentIndex();
    if (!index.isValid() || index.row() == 0) {
        return;
    }
    fieldTableModel_.moveUp(index.row());
}

void CardEditDialog::onFieldDown() {
    auto index = ui->fieldsTable->currentIndex();
    if (!index.isValid() || index.row() == fieldTableModel_.rowCount() - 1) {
        return;
    }
    fieldTableModel_.moveDown(index.row());
}

void CardEditDialog::fieldTableContextMenuRequested(QPoint pos) {
    auto index = ui->fieldsTable->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    fieldTableContextMenu_.popup(ui->fieldsTable->viewport()->mapToGlobal(pos));
}

void CardEditDialog::fieldTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &) {
    if (!current.isValid()) {
        return;
    }
    auto field = fieldTableModel_.at(current.row());
    fieldUpAction_.setEnabled(current.row() != 0);
    fieldDownAction_.setEnabled(current.row() != fieldTableModel_.rowCount() - 1);
    fieldGenerateAction_.setEnabled(field->type() == FieldType::PIN || field->type() == FieldType::UNIX_PASSWORD ||
                                    field->type() == FieldType::LONG_PASSWORD ||
                                    field->type() == FieldType::SHORT_PASSWORD);
}
