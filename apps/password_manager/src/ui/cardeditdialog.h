//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "card.h"
#include <QDialog>

namespace Ui {
class CardEditDialog;
}

class EditFieldListModel;

class CardEditDialog final : public QDialog {
    Q_OBJECT

  public:
    explicit CardEditDialog(QWidget *parent);
    ~CardEditDialog();

    void setCard(const Card &card);
    const Card &card() const { return card_; }

    virtual void done(int code) override;

  private:
    void setupActions();
    void setupFieldTable();
    void setupFieldTableContextMenu();

    // Actions
    void onAddField();
    void onDeleteField();
    void onFieldUp();
    void onFieldDown();
    void onGenerate();
    void fieldTableContextMenuRequested(QPoint pos);
    void fieldTableCurrentRowChanged(const QModelIndex &, const QModelIndex &);

  private:
    std::unique_ptr<Ui::CardEditDialog> ui;
    EditFieldListModel *model_;

    Card card_;

    // Field table actions
    QAction *fieldAddAction_;
    QAction *fieldDeleteAction_;
    QAction *fieldUpAction_;
    QAction *fieldDownAction_;
    QAction *fieldGenerateAction_;
    QMenu *fieldTableContextMenu_;
};
