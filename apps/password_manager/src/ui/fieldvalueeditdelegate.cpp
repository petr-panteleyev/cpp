//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "fieldvalueeditdelegate.h"
#include "creditcardtype.h"
#include "editfieldlistmodel.h"
#include "field.h"
#include "fieldtype.h"
#include "translations.h"
#include <QComboBox>
#include <QDateEdit>

QWidget *FieldValueEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const {
    switch (index.column()) {
        case EditFieldListModel::FIELD_TABLE_NAME_COLUMN:
            return QStyledItemDelegate::createEditor(parent, option, index);

        case EditFieldListModel::FIELD_TABLE_TYPE_COLUMN: {
            auto comboBox = new QComboBox(parent);
            for (const FieldType &f : FieldType::values()) {
                comboBox->addItem(Translations::translate(f), f.ordinal());
            }
            return comboBox;
        }

        case EditFieldListModel::FIELD_TABLE_VALUE_COLUMN: {
            const auto field = getModel(index)->at(index.row());
            if (field->type() == FieldType::CARD_TYPE) {
                auto comboBox = new QComboBox(parent);
                for (const CreditCardType &type : CreditCardType::values()) {
                    comboBox->addItem(type.cardTypeName(), type.ordinal());
                }
                return comboBox;
            } else {
                return QStyledItemDelegate::createEditor(parent, option, index);
            }
        }

        default: return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void FieldValueEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    const auto field = getModel(index)->at(index.row());

    switch (index.column()) {
        case EditFieldListModel::FIELD_TABLE_TYPE_COLUMN: {
            auto comboBox = reinterpret_cast<QComboBox *>(editor);
            comboBox->setCurrentIndex(field->type().ordinal());
            break;
        }

        case EditFieldListModel::FIELD_TABLE_VALUE_COLUMN: {
            if (field->type() == FieldType::CARD_TYPE) {
                auto comboBox = reinterpret_cast<QComboBox *>(editor);
                auto index = field->value().toUInt();
                comboBox->setCurrentIndex(index);
            } else {
                QStyledItemDelegate::setEditorData(editor, index);
            }
            break;
        }

        default: QStyledItemDelegate::setEditorData(editor, index);
    }
}

void FieldValueEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    auto field = getModel(index)->at(index.row());

    switch (index.column()) {
        case EditFieldListModel::FIELD_TABLE_TYPE_COLUMN: {
            auto comboBox = reinterpret_cast<QComboBox *>(editor);
            auto ordinal = comboBox->currentData().toUInt();
            auto &newType = FieldType::valueOf(ordinal);
            if (newType != field->type()) {
                auto newValue = field->convertValue(newType);
                field->setType(newType);
                field->setValue(newValue);
            }
        }

        case EditFieldListModel::FIELD_TABLE_VALUE_COLUMN: {
            if (field->type() == FieldType::CARD_TYPE) {
                auto comboBox = reinterpret_cast<QComboBox *>(editor);
                auto ordinal = comboBox->currentData().toUInt();
                field->setValue(ordinal);
            } else if (field->type() == FieldType::DATE || field->type() == FieldType::EXPIRATION_MONTH) {
                auto dateEdit = reinterpret_cast<QDateEdit *>(editor);
                field->setValue(dateEdit->date());
            } else {
                QStyledItemDelegate::setModelData(editor, model, index);
            }
        }

        default: QStyledItemDelegate::setModelData(editor, model, index);
    }
}
