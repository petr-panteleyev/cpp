/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "editfieldlistmodel.h"
#include "translations.h"
#include <QComboBox>
#include <QList>

EditFieldListModel::EditFieldListModel(QObject *parent) : QAbstractItemModel(parent) {
}

QVariant EditFieldListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
        case FIELD_TABLE_NAME_COLUMN: return tr("Name");
        case FIELD_TABLE_TYPE_COLUMN: return tr("Type");
        case FIELD_TABLE_VALUE_COLUMN: return tr("Value");
        default: return QVariant();
    }
}

bool EditFieldListModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) {
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

QVariant EditFieldListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    auto field = fields_.at(index.row());

    switch (index.column()) {
        case FIELD_TABLE_NAME_COLUMN: {
            return role == Qt::DisplayRole || role == Qt::EditRole ? field->name() : QVariant();
        };
        case FIELD_TABLE_TYPE_COLUMN: {
            return role == Qt::DisplayRole ? Translations::translate(field->type()) : QVariant();
        }
        case FIELD_TABLE_VALUE_COLUMN: {
            if (role == Qt::DisplayRole)
                return field->getValueAsString();
            else if (role == Qt::EditRole) {
                return field->value();
            } else {
                return QVariant();
            }
        }
        default: return QVariant();
    }
}

bool EditFieldListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole) {
        return false;
    }

    if (data(index, role) != value) {
        auto field = at(index.row());

        switch (index.column()) {
            case FIELD_TABLE_NAME_COLUMN: field->setName(value.toString()); break;
            case FIELD_TABLE_VALUE_COLUMN: field->setValue(value.toString()); break;
            default: return false;
        }

        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags EditFieldListModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
