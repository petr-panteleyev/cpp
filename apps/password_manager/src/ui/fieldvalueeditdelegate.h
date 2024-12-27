//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef FIELDVALUEEDITDELEGATE_H
#define FIELDVALUEEDITDELEGATE_H

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

#endif // FIELDVALUEEDITDELEGATE_H
