//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "newcarddialog.h"
#include "picture.h"
#include "qthelpers.h"
#include "recordtype.h"
#include "timeutil.h"
#include "ui_newcarddialog.h"

namespace {

void initTypeComboBox(std::unique_ptr<Ui::NewCardDialog> &ui) {
    for (const RecordType &type : RecordType::values()) {
        ui->typeComboBox->addItem(type.picture().icon(), type.translation(), type.ordinal());
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
        auto translatedName = QApplication::translate("RecordType", f.name().toStdString().c_str());
        fields.emplace_back(f.type(), translatedName, f.value());
    }

    return Card(picture, ui->titleEdit->text(), TimeUtil::currentTimeMillis(), fields);
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
