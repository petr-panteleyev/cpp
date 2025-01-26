//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "currencywindow.h"
#include "currency.h"
#include "datacache.h"
#include "globalcontext.h"
#include "qnamespace.h"
#include "qvariant.h"
#include "settings.h"
#include "ui_currencywindow.h"
#include <QSortFilterProxyModel>

using GlobalContext::cache;

using std::make_unique;

class CurrencyWindow::CurrencyFilterModel final : public QSortFilterProxyModel {
  public:
    explicit CurrencyFilterModel() {}
    ~CurrencyFilterModel(){};

    int columnCount(const QModelIndex &parent = TOP_LEVEL) const override { return 2; }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole) {
            return QVariant();
        }

        switch (section) {
            case 0: return "Название";
            case 1: return "Описание";
            default: return QVariant();
        }
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        auto currency = cache().getCurrency(mapToSource(index).row());
        switch (index.column()) {
            case 0: return currency->symbol();
            case 1: return currency->description();
        }

        return QVariant();
    };

  private:
    static inline QModelIndex TOP_LEVEL = QModelIndex();
};

CurrencyWindow::CurrencyWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::CurrencyWindow>()}, model_{make_unique<CurrencyFilterModel>()} {
    ui->setupUi(this);

    model_->setSourceModel(cache().getCurrencyItemModel());
    ui->currencyTableView->setModel(model_.get());

    auto header = ui->currencyTableView->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::Stretch);

    connect(ui->actionClose, &QAction::triggered, [this]() { close(); });
}

CurrencyWindow::~CurrencyWindow() {
}

void CurrencyWindow::hideEvent(QHideEvent *event) {
    Settings::saveWindowDimensions(this);
    QMainWindow::hideEvent(event);
}
