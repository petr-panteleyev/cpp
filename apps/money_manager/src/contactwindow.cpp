//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "contactwindow.h"
#include "contact.h"
#include "datacache.h"
#include "mainwindow.h"
#include "moneyrecorditemmodel.h"
#include "settings.h"
#include "translation.h"
#include "ui_contactwindow.h"
#include <QSortFilterProxyModel>

using std::make_unique;

namespace {

constexpr int COLUMN_NAME = 0;
constexpr int COLUMN_TYPE = 1;
constexpr int COLUMN_PHONE = 2;
constexpr int COLUMN_EMAIL = 3;

constexpr int COLUMN_COUNT = COLUMN_EMAIL + 1;

const std::unordered_map<int, QHeaderView::ResizeMode> RESIZE_MODES{
    {COLUMN_NAME, QHeaderView::Stretch},
    {COLUMN_TYPE, QHeaderView::Stretch},
    {COLUMN_PHONE, QHeaderView::Stretch},
    {COLUMN_EMAIL, QHeaderView::Stretch},
};

const std::array<QString, COLUMN_COUNT> COLUMN_NAMES{"Имя", "Тип", "Телефон", "E-mail"};

} // namespace

class ContactWindow::ContactFilterModel : public QSortFilterProxyModel {
  public:
    explicit ContactFilterModel() : typeOrdinal_{-1}, nameFilter_{} {}
    ~ContactFilterModel(){};

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
        auto contact = DataCache::cache().getContact(row);

        switch (index.column()) {
            case COLUMN_NAME: return contact.name();
            case COLUMN_TYPE: return Translation::translateContactType(contact.type());
            case COLUMN_PHONE: return contact.phone();
            case COLUMN_EMAIL: return contact.email();
        }

        return QVariant();
    };

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override {
        if (left.column() != right.column()) {
            return false;
        }

        auto leftContact = DataCache::cache().getContact(left.row());
        auto rightContact = DataCache::cache().getContact(right.row());

        switch (left.column()) {
            case COLUMN_NAME: return leftContact.name() < rightContact.name();
            case COLUMN_TYPE: return leftContact.type() < rightContact.type();
            case COLUMN_PHONE: return leftContact.phone() < rightContact.phone();
            case COLUMN_EMAIL: return leftContact.email() < rightContact.email();
        }
        return false;
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        if (typeOrdinal_ == -1 && nameFilter_.isEmpty()) {
            return true;
        }

        auto contact = DataCache::cache().getContact(sourceRow);

        bool accept = true;
        if (typeOrdinal_ != -1) {
            accept = accept && contact.type() == static_cast<unsigned>(typeOrdinal_);
        }
        if (!nameFilter_.isEmpty()) {
            accept = accept & contact.name().contains(nameFilter_, Qt::CaseInsensitive);
        }
        return accept;
    }

  private:
    int typeOrdinal_;
    QString nameFilter_;
};

ContactWindow::ContactWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::ContactWindow>()}, model_{make_unique<ContactFilterModel>()} {
    ui->setupUi(this);

    getMainWindow()->setupWindowMenu(ui->menuWindow);

    model_->setSourceModel(DataCache::cache().getContactItemModel());
    ui->contactTableView->setModel(model_.get());

    auto header = ui->contactTableView->horizontalHeader();
    for (const auto &entry : RESIZE_MODES) {
        header->setSectionResizeMode(entry.first, entry.second);
    }

    ui->typeComboBox->addItem("Все типы", -1);
    ui->typeComboBox->insertSeparator(1);
    std::for_each(ContactType::values().begin(), ContactType::values().end(), [this](const ContactType &type) {
        ui->typeComboBox->addItem(Translation::translateContactType(type.ordinal()), static_cast<int>(type.ordinal()));
    });
    connect(ui->typeComboBox, &QComboBox::currentIndexChanged, [this](int index) {
        int ordinal = ui->typeComboBox->currentData().toInt();
        model_->setTypeOrdinal(ordinal);
        ui->contactTableView->resizeColumnToContents(COLUMN_TYPE);
    });

    connect(ui->filterEdit, &QLineEdit::textChanged, [this](const auto &text) {
        model_->setNameFilter(text);
        ui->contactTableView->resizeColumnToContents(COLUMN_NAME);
    });

    connect(ui->closeAction, &QAction::triggered, [this]() { close(); });
    model_->sort(COLUMN_NAME);

    Settings::loadWindowDimensions(this);
}

ContactWindow::~ContactWindow() {
}

void ContactWindow::hideEvent(QHideEvent *event) {
    Settings::saveWindowDimensions(this);
    QMainWindow::hideEvent(event);
}
