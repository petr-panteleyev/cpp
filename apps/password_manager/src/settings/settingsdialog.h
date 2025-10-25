//  Copyright © 2024 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "fonttype.h"
#include "settings.h"
#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class QLineEdit;

class SettingsDialog : public QDialog {
    Q_OBJECT

  public:
    explicit SettingsDialog(QWidget *parent);
    ~SettingsDialog();

    virtual void done(int code) override;

  protected:
    virtual void showEvent(QShowEvent *event) override;

  private:
    void onFieldNameColorButton(Settings::Color color, QPushButton *button);

    void setupColorButtons(bool connectSignal);
    void setupColorButton(Settings::Color color, QPushButton *button, bool connectSignal);

    void setupFontButtons();

    void onPasswordTypeSelected(int index);
    void onPasswordLengthSelected(int index);
    void onFontButtonClicked(Settings::FontType fontType, QLineEdit *fontEdit);

  private:
    std::unique_ptr<Ui::SettingsDialog> ui;

    Settings::ColorMap colors_;
    Settings::PasswordTypePtrMap passwords_;
    Settings::FontPtrMap fonts_;
};
