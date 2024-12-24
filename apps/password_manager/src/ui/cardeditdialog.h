//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CARDEDITDIALOG_H
#define CARDEDITDIALOG_H

#include <QDialog>
#include <QMenu>

namespace Ui {
class CardEditDialog;
}

class Card;
class EditFieldListModel;

class CardEditDialog final : public QDialog {
    Q_OBJECT

  public:
    explicit CardEditDialog(QWidget *parent = nullptr);
    ~CardEditDialog();

    void setCard(const Card &card);
    const std::shared_ptr<Card> &card() const { return card_; }

    virtual void done(int code) override;

  private:
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
    std::unique_ptr<EditFieldListModel> model_;

    std::shared_ptr<Card> card_;

    // Field table actions
    QAction fieldAddAction_;
    QAction fieldDeleteAction_;
    QAction fieldUpAction_;
    QAction fieldDownAction_;
    QAction fieldGenerateAction_;
    QMenu fieldTableContextMenu_;
};

#endif // CARDEDITDIALOG_H
