/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "boardsizedialog.h"
#include "qslider.h"
#include "ui_boardsizedialog.h"

BoardSizeDialog::BoardSizeDialog(QWidget *parent) : QDialog(parent), ui(new Ui::BoardSizeDialog) {
    ui->setupUi(this);

    adjustMinesSlider();

    connect(ui->widthSlider, &QSlider::valueChanged, this, &BoardSizeDialog::onWidthValueChanged);
    connect(ui->heightSlider, &QSlider::valueChanged, this, &BoardSizeDialog::onHeightValueChanged);
    connect(ui->minesSlider, &QSlider::valueChanged, this, &BoardSizeDialog::onMinesValueChanged);
}

BoardSizeDialog::~BoardSizeDialog() {
    delete ui;
}

BoardSize BoardSizeDialog::boardSize() const {
    return BoardSize::boardSize(ui->widthSlider->value(), ui->heightSlider->value(), ui->minesSlider->value());
}

void BoardSizeDialog::adjustMinesSlider() {
    auto maxMines = (ui->widthSlider->value() - 1) * (ui->heightSlider->value() - 1);
    ui->minesSlider->setMaximum(maxMines);
    ui->minesMaxLabel->setText(QString::number(maxMines));
}

void BoardSizeDialog::onWidthValueChanged(int value) {
    ui->widthValueLabel->setText(QString::number(value));
    adjustMinesSlider();
}

void BoardSizeDialog::onHeightValueChanged(int value) {
    ui->heightValueLabel->setText(QString::number(value));
    adjustMinesSlider();
}

void BoardSizeDialog::onMinesValueChanged(int value) {
    ui->minesValueLabel->setText(QString::number(value));
}
