/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "cardeditdialog.h"
#include "fieldvalueeditdelegate.h"
#include "picture.h"
#include "ui_cardeditdialog.h"
#include <QValidator>

class NotEmptyValidator : public QValidator {
  public:
    virtual QValidator::State validate(QString &input, int &pos) const override {
        return input.isEmpty() ? QValidator::State::Invalid : QValidator::State::Acceptable;
    }
};

CardEditDialog::CardEditDialog(const Card &card, QWidget *parent)
    : QDialog(parent), ui(new Ui::CardEditDialog), card_{card}, fieldTableModel_{this} {
    ui->setupUi(this);

    fieldTableModel_.setFields(card_.fields());

    ui->notesEditor->appendPlainText(card.note());
    ui->nameEditor->setText(card.name());
    ui->nameEditor->setValidator(new NotEmptyValidator());

    ui->fieldsTable->setModel(&fieldTableModel_);
    ui->fieldsTable->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->fieldsTable->setItemDelegateForColumn(1, new FieldValueEditDelegate());
    ui->fieldsTable->setItemDelegateForColumn(2, new FieldValueEditDelegate());

    auto header = ui->fieldsTable->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::Stretch);

    initPictureComboBox();
}

CardEditDialog::~CardEditDialog() {
    delete ui;
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
