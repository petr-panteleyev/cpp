/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "fieldtableitemmodel.h"
#include "creditcardtype.h"
#include <QColor>

static const QString MASK = "*****";

QVariant FieldTableItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || (std::size_t)index.row() >= items_.size()) {
        return QVariant();
    }

    auto field = items_.at(index.row());

    switch (index.column()) {
        case 0: {
            switch (role) {
                case Qt::DisplayRole: return field->name();
                case Qt::TextAlignmentRole: return Qt::AlignRight;
                case Qt::ForegroundRole: return QColorConstants::Blue;
                default: return QVariant(); ;
            }
        }
        case 1: {
            switch (role) {
                case Qt::DisplayRole: return field->showContent() ? field->getValueAsString() : MASK;
                case Qt::TextAlignmentRole: return Qt::AlignLeft;
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

void FieldTableItemModel::toggleMasking(const QModelIndex &index, const FieldPtr &field) {
    field->toggleShow();
    emit dataChanged(index, index, {Qt::DisplayRole});
}
