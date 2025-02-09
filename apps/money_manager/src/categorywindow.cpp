//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "categorywindow.h"
#include "category.h"
#include "datacache.h"
#include "mainwindow.h"
#include "moneyrecorditemmodel.h"
#include "settings.h"
#include "translation.h"
#include "ui_categorywindow.h"
#include <QSortFilterProxyModel>
#include <algorithm>

using std::make_unique;

namespace {

constexpr int COLUMN_NAME = 0;
constexpr int COLUMN_TYPE = 1;
constexpr int COLUMN_COMMENT = 2;

constexpr int COLUMN_COUNT = COLUMN_COMMENT + 1;

const std::unordered_map<int, QHeaderView::ResizeMode> RESIZE_MODES{
    {COLUMN_NAME, QHeaderView::ResizeToContents},
    {COLUMN_TYPE, QHeaderView::ResizeToContents},
    {COLUMN_COMMENT, QHeaderView::Stretch},
};

const std::array<QString, COLUMN_COUNT> COLUMN_NAMES{"Название", "Тип", "Комментарий"};

} // namespace

class CategoryWindow::CategoryFilterModel : public QSortFilterProxyModel {
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

    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMN_COUNT; };

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole || section >= COLUMN_COUNT) {
            return QVariant();
        }
        return COLUMN_NAMES[section];
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        int row = mapToSource(index).row();
        auto category = DataCache::cache().getCategory(row);

        switch (index.column()) {
            case COLUMN_NAME: return category.name();
            case COLUMN_TYPE: return Translation::translateCategoryType(category.type());
            case COLUMN_COMMENT: return category.comment();
        }

        return QVariant();
    }

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override {
        if (left.column() != right.column()) {
            return false;
        }

        auto leftCategory = DataCache::cache().getCategory(left.row());
        auto rightCategory = DataCache::cache().getCategory(right.row());

        switch (left.column()) {
            case COLUMN_NAME: return leftCategory.name() < rightCategory.name();
            case COLUMN_TYPE: return leftCategory.type() < rightCategory.type();
            case COLUMN_COMMENT: return false;
        }
        return false;
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        if (typeOrdinal_ == -1 && nameFilter_.isEmpty()) {
            return true;
        }

        auto category = DataCache::cache().getCategory(sourceRow);

        bool accept = true;
        if (typeOrdinal_ != -1) {
            accept = accept && category.type() == static_cast<unsigned>(typeOrdinal_);
        }
        if (!nameFilter_.isEmpty()) {
            accept = accept & category.name().contains(nameFilter_, Qt::CaseInsensitive);
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

    getMainWindow()->setupWindowMenu(ui->menuWindow);

    model_->setSourceModel(DataCache::cache().getCategoryItemModel());
    ui->categoryTableView->setModel(model_.get());

    auto header = ui->categoryTableView->horizontalHeader();
    for (const auto &entry : RESIZE_MODES) {
        header->setSectionResizeMode(entry.first, entry.second);
    }

    ui->typeComboBox->addItem("Все типы", -1);
    ui->typeComboBox->insertSeparator(1);
    std::for_each(CategoryType::values().begin(), CategoryType::values().end(), [this](const CategoryType &type) {
        ui->typeComboBox->addItem(Translation::translateCategoryType(type.ordinal()), static_cast<int>(type.ordinal()));
    });
    connect(ui->typeComboBox, &QComboBox::currentIndexChanged, [this](int index) {
        int ordinal = ui->typeComboBox->currentData().toInt();
        model_->setTypeOrdinal(ordinal);
        ui->categoryTableView->resizeColumnToContents(COLUMN_TYPE);
    });

    connect(ui->filterEdit, &QLineEdit::textChanged, [this](const auto &text) {
        model_->setNameFilter(text);
        ui->categoryTableView->resizeColumnToContents(COLUMN_NAME);
    });

    connect(ui->actionClose, &QAction::triggered, [this]() { close(); });

    Settings::loadWindowDimensions(this);
}

CategoryWindow::~CategoryWindow() {
}

void CategoryWindow::hideEvent(QHideEvent *event) {
    Settings::saveWindowDimensions(this);
    QMainWindow::hideEvent(event);
}
