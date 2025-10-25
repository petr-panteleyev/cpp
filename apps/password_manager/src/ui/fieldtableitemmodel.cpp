//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "fieldtableitemmodel.h"
#include "creditcardtype.h"
#include "field.h"
#include "fieldtype.h"
#include "picture.h"
#include "settings.h"

namespace {

const QString MASK = "*****";
const QColor LINK_COLOR{0, 0, 255};

} // namespace

void FieldTableItemModel::setItems(const std::vector<Field> &items) {
    beginResetModel();
    items_ = items;
    endResetModel();
}

QVariant FieldTableItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || (std::size_t)index.row() >= items_.size()) {
        return QVariant();
    }

    const auto field = fieldAtIndex(index.row());

    switch (index.column()) {
        case 0: {
            switch (role) {
                case Qt::DisplayRole: return field->name();
                case Qt::TextAlignmentRole: return Qt::AlignRight;
                case Qt::ForegroundRole: return Settings::getColor(Settings::Color::FieldName);
                default: return QVariant();
            }
        }
        case 1: {
            switch (role) {
                case Qt::DisplayRole: return field->showContent() ? field->getValueAsString() : MASK;
                case Qt::TextAlignmentRole: return Qt::AlignLeft;
                case Qt::ForegroundRole: {
                    if (field->type() == FieldType::LINK) {
                        return LINK_COLOR;
                    } else {
                        return Settings::getColor(Settings::Color::FieldValue);
                    }
                }
                case Qt::DecorationRole: {
                    if (field->type() == FieldType::CARD_TYPE) {
                        auto ordinal = field->value().toUInt();
                        const auto &cardType = CreditCardType::valueOf(ordinal);
                        return cardType.picture().icon();
                    } else {
                        return QVariant();
                    }
                }

                default: return QVariant();
            }
        }
        default: return QVariant();
    }
}

void FieldTableItemModel::toggleMasking(const QModelIndex &index, Field &field) {
    field.toggleShow();
    emit dataChanged(index, index, {Qt::DisplayRole});
}
