/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "settings.h"
#include <QDialog>

namespace Ui {
class SettingsDialog;
}

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

    void onPasswordTypeSelected(int index);
    void onPasswordLengthSelected(int index);
    void onUpperCaseClicked(bool checked);
    void onLowerCaseClicked(bool checked);
    void onDigitsClicked(bool checked);
    void onSymbolsClicked(bool checked);

  private:
    Ui::SettingsDialog *ui;

    Settings::ColorMap           colors_;
    Settings::PasswordTypePtrMap passwords_;
};

#endif // SETTINGSDIALOG_H
