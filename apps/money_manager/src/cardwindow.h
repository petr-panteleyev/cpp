//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QMainWindow>

namespace Ui {
class CardWindow;
}

class CardWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit CardWindow(QWidget *parent);
    ~CardWindow();

  protected:
    virtual void hideEvent(QHideEvent *event) override;

  private:
    std::unique_ptr<Ui::CardWindow> ui;

    class CardFilterModel;
    std::unique_ptr<CardFilterModel> model_;
};

#endif // CARDWINDOW_H
