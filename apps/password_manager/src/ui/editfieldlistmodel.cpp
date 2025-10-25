//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "editfieldlistmodel.h"
#include "field.h"
#include "fieldtype.h"
#include "translations.h"

EditFieldListModel::EditFieldListModel(QObject *parent) : QAbstractItemModel(parent) {
}

QVariant EditFieldListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
        case FIELD_TABLE_NAME_COLUMN: return "Название";
        case FIELD_TABLE_TYPE_COLUMN: return "Тип";
        case FIELD_TABLE_VALUE_COLUMN: return "Значение";
        default: return QVariant();
    }
}

QVariant EditFieldListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const auto field = at(index.row());

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

void EditFieldListModel::setFields(const std::vector<Field> &fields) {
    beginResetModel();
    fields_ = fields;
    endResetModel();
}

void EditFieldListModel::addField() {
    beginInsertRows(QModelIndex(), fields_.size(), fields_.size());
    fields_.emplace_back(FieldType::STRING, "Field", "");
    endInsertRows();
}

void EditFieldListModel::deleteField(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    fields_.erase(std::next(fields_.begin(), row));
    endRemoveRows();
}

void EditFieldListModel::moveUp(int row) {
    beginMoveRows(QModelIndex(), row, row, QModelIndex(), row - 1);
    std::iter_swap(std::next(fields_.begin(), row), std::next(fields_.begin(), row - 1));
    endMoveRows();
}

void EditFieldListModel::moveDown(int row) {
    beginMoveRows(QModelIndex(), row, row, QModelIndex(), row + 2);
    std::iter_swap(std::next(fields_.begin(), row), std::next(fields_.begin(), row + 1));
    endMoveRows();
}

void EditFieldListModel::setFieldValue(int row, const QVariant &value) {
    std::next(fields_.begin(), row)->setValue(value);
    auto updateIndex = index(row, FIELD_TABLE_VALUE_COLUMN);
    emit dataChanged(updateIndex, updateIndex, {Qt::EditRole});
}
