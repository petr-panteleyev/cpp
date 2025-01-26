//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "categorywindow.h"
#include "category.h"
#include "datacache.h"
#include "globalcontext.h"
#include "qnamespace.h"
#include "settings.h"
#include "translation.h"
#include "ui_categorywindow.h"
#include <QSortFilterProxyModel>
#include <algorithm>

using GlobalContext::cache;
using std::make_unique;

class CategoryWindow::CategoryFilterModel : public QSortFilterProxyModel {
  public:
    static constexpr int COLUMN_NAME = 0;
    static constexpr int COLUMN_TYPE = 1;
    static constexpr int COLUMN_COMMENT = 2;

  public:
    explicit CategoryFilterModel() : typeOrdinal_{-1}, nameFilter_{} {}
    ~CategoryFilterModel(){};

    void setTypeOrdinal(int ordinal) {
        typeOrdinal_ = ordinal;
        invalidateRowsFilter();
    }

    void setNameFilter(const QString &filter) {
        nameFilter_ = filter;
        invalidateRowsFilter();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 3; };

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole) {
            return QVariant();
        }

        switch (section) {
            case COLUMN_NAME: return "Название";
            case COLUMN_TYPE: return "Тип";
            case COLUMN_COMMENT: return "Комментарий";
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
            case COLUMN_NAME: return category->name();
            case COLUMN_TYPE: return Translation::translate(category->type());
            case COLUMN_COMMENT: return category->comment();
        }

        return QVariant();
    }

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override {
        if (left.column() != right.column()) {
            return false;
        }

        auto leftCategory = cache().getCategory(left.row());
        auto rightCategory = cache().getCategory(right.row());

        switch (left.column()) {
            case COLUMN_NAME: return leftCategory->name() < rightCategory->name();
            case COLUMN_TYPE: return leftCategory->type().ordinal() < rightCategory->type().ordinal();
            case COLUMN_COMMENT: return false;
        }
        return false;
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        if (typeOrdinal_ == -1 && nameFilter_.isEmpty()) {
            return true;
        }

        auto category = cache().getCategory(sourceRow);

        bool accept = true;
        if (typeOrdinal_ != -1) {
            accept = accept && category->type().ordinal() == static_cast<unsigned>(typeOrdinal_);
        }
        if (!nameFilter_.isEmpty()) {
            accept = accept & category->name().contains(nameFilter_, Qt::CaseInsensitive);
        }
        return accept;
    }

  private:
    int typeOrdinal_;
    QString nameFilter_;
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

    ui->typeComboBox->addItem("Все типы", -1);
    ui->typeComboBox->insertSeparator(1);
    std::for_each(CategoryType::values().begin(), CategoryType::values().end(), [this](const CategoryType &type) {
        ui->typeComboBox->addItem(Translation::translate(type), static_cast<int>(type.ordinal()));
    });
    connect(ui->typeComboBox, &QComboBox::currentIndexChanged, [this](int index) {
        int ordinal = ui->typeComboBox->currentData().toInt();
        model_->setTypeOrdinal(ordinal);
        ui->categoryTableView->resizeColumnToContents(CategoryFilterModel::COLUMN_TYPE);
    });

    connect(ui->filterEdit, &QLineEdit::textChanged, [this](const auto &text) {
        model_->setNameFilter(text);
        ui->categoryTableView->resizeColumnToContents(CategoryFilterModel::COLUMN_NAME);
    });

    connect(ui->actionClose, &QAction::triggered, [this]() { close(); });
}

CategoryWindow::~CategoryWindow() {
}

void CategoryWindow::hideEvent(QHideEvent *event) {
    Settings::saveWindowDimensions(this);
    QMainWindow::hideEvent(event);
}
