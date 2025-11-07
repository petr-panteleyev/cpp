//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "boardsizedialog.hpp"

BoardSizeDialog::BoardSizeDialog(QWidget *parent) : QDialog{parent}, ui{std::make_unique<Ui::BoardSizeDialog>()} {
    ui->setupUi(this);

    adjustMinesSlider();

    connect(ui->widthSlider, &QSlider::valueChanged, [this](auto value) {
        ui->widthValueLabel->setText(QString::number(value));
        adjustMinesSlider();
    });
    connect(ui->heightSlider, &QSlider::valueChanged, [this](auto value) {
        ui->heightValueLabel->setText(QString::number(value));
        adjustMinesSlider();
    });
    connect(ui->minesSlider, &QSlider::valueChanged,
            [this](auto value) { ui->minesValueLabel->setText(QString::number(value)); });
}

BoardSize BoardSizeDialog::boardSize() const {
    return BoardSize::boardSize(ui->widthSlider->value(), ui->heightSlider->value(), ui->minesSlider->value());
}

void BoardSizeDialog::adjustMinesSlider() {
    auto maxMines = (ui->widthSlider->value() - 1) * (ui->heightSlider->value() - 1);
    ui->minesSlider->setMaximum(maxMines);
    ui->minesMaxLabel->setText(QString::number(maxMines));
}
