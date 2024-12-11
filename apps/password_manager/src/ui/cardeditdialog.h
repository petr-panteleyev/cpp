/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef CARDEDITDIALOG_H
#define CARDEDITDIALOG_H

#include "editfieldlistmodel.h"
#include <QAction>
#include <QDialog>
#include <QMenu>
#include <card.h>

namespace Ui {
class CardEditDialog;
}

class CardEditDialog : public QDialog {
    Q_OBJECT

  public:
    explicit CardEditDialog(const Card &card, QWidget *parent = nullptr);
    ~CardEditDialog();

    const Card &card() const { return card_; }

    virtual void done(int code) override;

  private:
    void initPictureComboBox();
    void setupFieldTable();
    void setupFieldTableContextMenu();

  private slots:
    void onAddField();
    void onDeleteField();
    void onFieldUp();
    void onFieldDown();
    void fieldTableContextMenuRequested(QPoint pos);
    void fieldTableCurrentRowChanged(const QModelIndex &, const QModelIndex &);

  private:
    Ui::CardEditDialog *ui;

    Card               card_;
    EditFieldListModel fieldTableModel_;

    // Field table actions
    QAction fieldAddAction_;
    QAction fieldDeleteAction_;
    QAction fieldUpAction_;
    QAction fieldDownAction_;
    QAction fieldGenerateAction_;
    QMenu   fieldTableContextMenu_;
};

#endif // CARDEDITDIALOG_H
