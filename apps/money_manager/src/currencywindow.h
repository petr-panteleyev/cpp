//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CURRENCYWINDOW_H
#define CURRENCYWINDOW_H

#include <QMainWindow>

namespace Ui {
class CurrencyWindow;
}

class CurrencyWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit CurrencyWindow(QWidget *parent = nullptr);
    ~CurrencyWindow();

  protected:
    virtual void hideEvent(QHideEvent *event) override;

  private:
    std::unique_ptr<Ui::CurrencyWindow> ui;

    class CurrencyFilterModel;
    std::unique_ptr<CurrencyFilterModel> model_;
};

#endif // CURRENCYWINDOW_H
