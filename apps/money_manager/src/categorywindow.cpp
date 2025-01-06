//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "categorywindow.h"
#include "category.h"
#include "datacache.h"
#include "globalcontext.h"
#include "ui_categorywindow.h"
#include <QSortFilterProxyModel>

using GlobalContext::cache;
using std::make_unique;

class CategoryWindow::CategoryFilterModel : public QSortFilterProxyModel {
  public:
    explicit CategoryFilterModel() {}
    ~CategoryFilterModel(){};

    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; };

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole) {
            return QVariant();
        }

        switch (section) {
            case 0: return "Тип";
            case 1: return "Название";
            case 2: return "Комментарий";
            default: return QVariant();
        }
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        int row = mapToSource(index).row();
        auto category = cache().getCategory(row);

        switch (index.column()) {
            case 0: return category->name();
            case 1: return QString::fromStdString(category->type().name());
            case 2: return category->comment();
        }

        return QVariant();
    };
};

CategoryWindow::CategoryWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::CategoryWindow>()}, model_{make_unique<CategoryFilterModel>()} {
    ui->setupUi(this);

    model_->setSourceModel(cache().getCategoryItemModel());
    ui->categoryTableView->setModel(model_.get());

    auto header = ui->categoryTableView->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(2, QHeaderView::Stretch);

    connect(ui->actionClose, &QAction::triggered, [this]() { close(); });
}

CategoryWindow::~CategoryWindow() {
}
