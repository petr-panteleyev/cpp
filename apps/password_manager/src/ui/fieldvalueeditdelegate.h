//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include <QStyledItemDelegate>

class EditFieldListModel;

class FieldValueEditDelegate : public QStyledItemDelegate {
  public:
    FieldValueEditDelegate(QObject *parent) : QStyledItemDelegate{parent} {}

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

  private:
    static const EditFieldListModel *getModel(const QModelIndex &index) {
        return reinterpret_cast<const EditFieldListModel *>(index.model());
    }
};
