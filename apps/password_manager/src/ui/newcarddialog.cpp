//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "newcarddialog.hpp"
#include "picture.hpp"
#include "qthelpers.hpp"
#include "recordtype.hpp"
#include "timeutil.hpp"
#include "ui_newcarddialog.h"

namespace {

void initTypeComboBox(std::unique_ptr<Ui::NewCardDialog> &ui) {
    for (const RecordType &type : RecordType::values()) {
        ui->typeComboBox->addItem(type.picture().icon(), QString(type.translation()), type.ordinal());
        if (type == RecordType::PASSWORD) {
            ui->typeComboBox->setCurrentIndex(ui->typeComboBox->count() - 1);
        }
    }
}

void initPictureComboBox(std::unique_ptr<Ui::NewCardDialog> &ui) {
    for (const Picture &picture : Picture::values()) {
        ui->pictureComboBox->addItem(picture.icon(), "", picture.ordinal());
        if (picture == Picture::GENERIC) {
            ui->pictureComboBox->setCurrentIndex(ui->pictureComboBox->count() - 1);
        }
    }
}

} // namespace

NewCardDialog::NewCardDialog(QWidget *parent) : QDialog{parent}, ui{std::make_unique<Ui::NewCardDialog>()} {
    ui->setupUi(this);

    ::initTypeComboBox(ui);
    ::initPictureComboBox(ui);

    connect(ui->typeComboBox, &QComboBox::currentIndexChanged, this, &NewCardDialog::onTypeComboBoxCurrentIndexChanged);
}

NewCardDialog::~NewCardDialog() {
}

Card NewCardDialog::card() const {
    auto typeOrdinal = ui->typeComboBox->currentData().toUInt();
    auto &type = RecordType::valueOf(typeOrdinal);

    auto pictureOrdinal = ui->pictureComboBox->currentData().toUInt();
    auto &picture = Picture::valueOf(pictureOrdinal);

    std::vector<Field> fields;
    fields.reserve(type.fields().size());

    for (auto &f : type.fields()) {
        fields.emplace_back(f.type(), f.name(), f.value());
    }

    return Card(picture, ui->titleEdit->text().toStdU16String(), TimeUtil::currentTimeMillis(), fields);
}

void NewCardDialog::onTypeComboBoxCurrentIndexChanged(int index) {
    if (index == -1) {
        return;
    }

    auto ordinal = ui->typeComboBox->currentData().toUInt();
    auto &type = RecordType::valueOf(ordinal);
    auto pictureOrdinal = type.picture().ordinal();

    auto pictureIndex = QtHelpers::indexOfData(*(ui->pictureComboBox), pictureOrdinal, Qt::UserRole);
    if (index != -1) {
        ui->pictureComboBox->setCurrentIndex(pictureIndex);
    }
}
