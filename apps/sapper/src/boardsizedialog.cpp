//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "boardsizedialog.h"
#include "ui_boardsizedialog.h"
#include <QSlider>
#include <memory>

namespace {

void adjustMinesSlider(const std::unique_ptr<Ui::BoardSizeDialog> &ui) {
    auto maxMines = (ui->widthSlider->value() - 1) * (ui->heightSlider->value() - 1);
    ui->minesSlider->setMaximum(maxMines);
    ui->minesMaxLabel->setText(QString::number(maxMines));
}

} // namespace

BoardSizeDialog::BoardSizeDialog(QWidget *parent) : QDialog{parent}, ui{std::make_unique<Ui::BoardSizeDialog>()} {
    ui->setupUi(this);

    ::adjustMinesSlider(ui);

    connect(ui->widthSlider, &QSlider::valueChanged, [this](auto value) {
        ui->widthValueLabel->setText(QString::number(value));
        ::adjustMinesSlider(ui);
    });
    connect(ui->heightSlider, &QSlider::valueChanged, [this](auto value) {
        ui->heightValueLabel->setText(QString::number(value));
        ::adjustMinesSlider(ui);
    });
    connect(ui->minesSlider, &QSlider::valueChanged,
            [this](auto value) { ui->minesValueLabel->setText(QString::number(value)); });
}

BoardSizeDialog::~BoardSizeDialog() {
}

BoardSize BoardSizeDialog::boardSize() const {
    return BoardSize::boardSize(ui->widthSlider->value(), ui->heightSlider->value(), ui->minesSlider->value());
}
