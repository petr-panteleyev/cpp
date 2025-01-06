//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "contactwindow.h"
#include "contact.h"
#include "datacache.h"
#include "globalcontext.h"
#include "qnamespace.h"
#include "ui_contactwindow.h"
#include <QSortFilterProxyModel>

using GlobalContext::cache;
using std::make_unique;

class ContactWindow::ContactFilterModel : public QSortFilterProxyModel {
  public:
    explicit ContactFilterModel() {}
    ~ContactFilterModel(){};

    int columnCount(const QModelIndex &parent = TOP_LEVEL) const override { return 4; };

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        int row = mapToSource(index).row();
        auto contact = cache().getContact(row);

        switch (index.column()) {
            case 0: return contact->name();
            case 1: return QString::fromStdString(contact->type().name());
            case 2: return contact->phone();
            case 3: return contact->email();
        }

        return QVariant();
    };

  private:
    static inline QModelIndex TOP_LEVEL = QModelIndex();
};

ContactWindow::ContactWindow(QWidget *parent)
    : QMainWindow{parent}, ui{make_unique<Ui::ContactWindow>()}, model_{make_unique<ContactFilterModel>()} {
    ui->setupUi(this);

    model_->setSourceModel(cache().getContactItemModel());
    ui->contactTableView->setModel(model_.get());

    connect(ui->closeAction, &QAction::triggered, [this]() { close(); });
}

ContactWindow::~ContactWindow() {
}
