/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "newcarddialog.h"
#include "field.h"
#include "picture.h"
#include "qthelpers.h"
#include "recordtype.h"
#include "timeutil.h"
#include "translations.h"
#include "ui_newcarddialog.h"

NewCardDialog::NewCardDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewCardDialog) {
    ui->setupUi(this);

    initTypeComboBox();
    initPictureComboBox();
}

NewCardDialog::~NewCardDialog() {
    delete ui;
}

void NewCardDialog::initTypeComboBox() {
    for (const RecordType &type : RecordType::values()) {
        ui->typeComboBox->addItem(type.picture().icon(), Translations::translate(type), type.ordinal());
        if (type == RecordType::PASSWORD) {
            ui->typeComboBox->setCurrentIndex(ui->typeComboBox->count() - 1);
        }
    }
}

void NewCardDialog::initPictureComboBox() {
    for (const Picture &picture : Picture::values()) {
        ui->pictureComboBox->addItem(picture.icon(), "", picture.ordinal());
        if (picture == Picture::GENERIC) {
            ui->pictureComboBox->setCurrentIndex(ui->pictureComboBox->count() - 1);
        }
    }
}

CardPtr NewCardDialog::card() const {
    auto  typeOrdinal = ui->typeComboBox->currentData().toUInt();
    auto &type = RecordType::valueOf(typeOrdinal);

    auto  pictureOrdinal = ui->pictureComboBox->currentData().toUInt();
    auto &picture = Picture::valueOf(pictureOrdinal);

    std::vector<FieldPtr> fields;
    fields.reserve(type.fields().size());   

    [[maybe_unused]]
    int fieldIndex = 0;
    for (auto &f : type.fields()) {
        auto translatedName = QApplication::translate("RecordType", f->name().toStdString().c_str());
        auto newField = std::make_shared<Field>(f->type(), translatedName, f->value());
        fields.push_back(newField);
    }

    return std::make_shared<Card>(picture, ui->titleEdit->text(), TimeUtil::currentTimeMillis(), fields);
}

void NewCardDialog::on_typeComboBox_currentIndexChanged(int index) {
    if (index == -1) {
        return;
    }

    auto  ordinal = ui->typeComboBox->currentData().toUInt();
    auto &type = RecordType::valueOf(ordinal);
    auto  pictureOrdinal = type.picture().ordinal();

    auto pictureIndex = QtHelpers::indexOfData(*(ui->pictureComboBox), pictureOrdinal);
    if (index != -1) {
        ui->pictureComboBox->setCurrentIndex(pictureIndex);
    }
}
