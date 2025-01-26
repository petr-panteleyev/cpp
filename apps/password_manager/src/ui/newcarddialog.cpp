//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "newcarddialog.h"
#include "card.h"
#include "field.h"
#include "picture.h"
#include "qthelpers.h"
#include "recordtype.h"
#include "timeutil.h"
#include "translations.h"
#include "ui_newcarddialog.h"

namespace {

void initTypeComboBox(std::unique_ptr<Ui::NewCardDialog> &ui) {
    for (const RecordType &type : RecordType::values()) {
        ui->typeComboBox->addItem(type.picture().icon(), Translations::translate(type), type.ordinal());
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

std::shared_ptr<Card> NewCardDialog::card() const {
    auto typeOrdinal = ui->typeComboBox->currentData().toUInt();
    auto &type = RecordType::valueOf(typeOrdinal);

    auto pictureOrdinal = ui->pictureComboBox->currentData().toUInt();
    auto &picture = Picture::valueOf(pictureOrdinal);

    std::vector<std::shared_ptr<Field>> fields;
    fields.reserve(type.fields().size());

    for (auto &f : type.fields()) {
        auto translatedName = QApplication::translate("RecordType", f->name().toStdString().c_str());
        auto newField = std::make_shared<Field>(f->type(), translatedName, f->value());
        fields.push_back(newField);
    }

    return std::make_shared<Card>(picture, ui->titleEdit->text(), TimeUtil::currentTimeMillis(), fields);
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
