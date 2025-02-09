//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "cardeditdialog.h"
#include "card.h"
#include "editfieldlistmodel.h"
#include "field.h"
#include "fieldtype.h"
#include "fieldvalueeditdelegate.h"
#include "generator.h"
#include "picture.h"
#include "qnamespace.h"
#include "qthelpers.h"
#include "settings.h"
#include "timeutil.h"
#include "ui_cardeditdialog.h"
#include <QMenu>
#include <QMessageBox>

using std::make_unique;

constexpr int TAB_FIELDS = 0;
constexpr int TAB_NOTES = 1;

static std::unordered_map<unsigned, Settings::PasswordType> GENERATOR_OPTIONS{
    {FieldType::PIN.ordinal(), Settings::PasswordType::Pin},
    {FieldType::UNIX_PASSWORD.ordinal(), Settings::PasswordType::Unix},
    {FieldType::SHORT_PASSWORD.ordinal(), Settings::PasswordType::Short},
    {FieldType::LONG_PASSWORD.ordinal(), Settings::PasswordType::Long},
};

class NotEmptyValidator : public QValidator {
  public:
    virtual QValidator::State validate(QString &input, int &pos) const override {
        return input.isEmpty() ? QValidator::State::Invalid : QValidator::State::Acceptable;
    }
};

CardEditDialog::CardEditDialog(QWidget *parent)
    : QDialog(parent), ui(make_unique<Ui::CardEditDialog>()), model_{new EditFieldListModel{this}},
      fieldAddAction_{new QAction{tr("Add"), this}}, fieldDeleteAction_{new QAction{tr("Delete"), this}},
      fieldUpAction_{new QAction{tr("Up"), this}}, fieldDownAction_{new QAction{tr("Down"), this}},
      fieldGenerateAction_(new QAction{tr("Generate"), this}), fieldTableContextMenu_{new QMenu{this}} {
    ui->setupUi(this);

    setupActions();
    setupFieldTable();
    setupFieldTableContextMenu();

    ui->nameEditor->setValidator(new NotEmptyValidator());

    ui->pictureComboBox->setStyleSheet("QComboBox { combobox-popup: 0; }");
    for (const Picture &picture : Picture::values()) {
        ui->pictureComboBox->addItem(picture.icon(), "", picture.ordinal());
    }
}

CardEditDialog::~CardEditDialog() {
}

void CardEditDialog::setCard(const Card &card) {
    card_ = card;

    model_->setFields(card.fields());

    ui->notesEditor->appendPlainText(card.note());
    ui->nameEditor->setText(card.name());

    // Fields and picture are editable for CARD only
    bool isCard = card.isCard();
    ui->tabWidget->setTabVisible(TAB_FIELDS, isCard);
    ui->tabWidget->setCurrentIndex(isCard ? TAB_FIELDS : TAB_NOTES);
    ui->pictureComboBox->setVisible(isCard);
    ui->pictureLabel->setVisible(isCard);

    // Picture
    auto pictureIndex = QtHelpers::indexOfData(*ui->pictureComboBox, card.picture().ordinal(), Qt::UserRole);
    if (pictureIndex != -1) {
        ui->pictureComboBox->setCurrentIndex(pictureIndex);
    }
}

void CardEditDialog::setupActions() {
    fieldAddAction_->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    connect(fieldAddAction_, &QAction::triggered, this, &CardEditDialog::onAddField);

    fieldDeleteAction_->setShortcut(QKeySequence(Qt::Key_Delete));
    connect(fieldDeleteAction_, &QAction::triggered, this, &CardEditDialog::onDeleteField);

    fieldGenerateAction_->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));
    connect(fieldGenerateAction_, &QAction::triggered, this, &CardEditDialog::onGenerate);

    fieldUpAction_->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Up));
    connect(fieldUpAction_, &QAction::triggered, this, &CardEditDialog::onFieldUp);

    fieldDownAction_->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Down));
    connect(fieldDownAction_, &QAction::triggered, this, &CardEditDialog::onFieldDown);
}

void CardEditDialog::setupFieldTable() {
    auto t = ui->fieldsTable;

    QtHelpers::addActions(
        t, {fieldAddAction_, fieldDeleteAction_, fieldGenerateAction_, fieldUpAction_, fieldDownAction_});

    t->setModel(model_);
    t->setEditTriggers(QAbstractItemView::DoubleClicked);
    t->setItemDelegateForColumn(EditFieldListModel::FIELD_TABLE_TYPE_COLUMN, new FieldValueEditDelegate(this));
    t->setItemDelegateForColumn(EditFieldListModel::FIELD_TABLE_VALUE_COLUMN, new FieldValueEditDelegate(this));

    connect(t->selectionModel(), &QItemSelectionModel::currentRowChanged, this,
            &CardEditDialog::fieldTableCurrentRowChanged);

    auto header = t->horizontalHeader();
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_NAME_COLUMN, QHeaderView::Stretch);
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_TYPE_COLUMN, QHeaderView::Stretch);
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_VALUE_COLUMN, QHeaderView::Stretch);
}

void CardEditDialog::setupFieldTableContextMenu() {
    QtHelpers::addActions(fieldTableContextMenu_, {fieldAddAction_, fieldDeleteAction_, nullptr, fieldGenerateAction_,
                                                   nullptr, fieldUpAction_, fieldDownAction_});

    connect(ui->fieldsTable, &QTableView::customContextMenuRequested, this,
            &CardEditDialog::fieldTableContextMenuRequested);
}

// TODO: do some validation here
void CardEditDialog::done(int code) {
    if (code == QDialog::Accepted) {
        auto newName = ui->nameEditor->text();
        if (newName.isEmpty()) {
            return;
        }

        card_.setModified(TimeUtil::currentTimeMillis());
        card_.setName(newName);

        card_.setFields(model_->fields());
        // picture
        auto pictureOrdinal = ui->pictureComboBox->currentData().toUInt();
        card_.setPicture(Picture::valueOf(pictureOrdinal));
        // note
        card_.setNote(ui->notesEditor->toPlainText());
    }
    QDialog::done(code);
}

void CardEditDialog::onAddField() {
    model_->addField();
}

void CardEditDialog::onDeleteField() {
    auto index = ui->fieldsTable->currentIndex();
    if (!index.isValid()) {
        return;
    }
    const auto field = model_->at(index.row());

    auto result = QMessageBox::question(this, tr("Delete"), tr("Are you sure to delete ") + field->name() + "?");
    if (result != QMessageBox::Yes) {
        return;
    }

    model_->deleteField(index.row());
}

void CardEditDialog::onFieldUp() {
    auto index = ui->fieldsTable->currentIndex();
    if (!index.isValid() || index.row() == 0) {
        return;
    }
    model_->moveUp(index.row());
}

void CardEditDialog::onFieldDown() {
    auto index = ui->fieldsTable->currentIndex();
    if (!index.isValid() || index.row() == model_->rowCount() - 1) {
        return;
    }
    model_->moveDown(index.row());
}

void CardEditDialog::onGenerate() {
    auto index = ui->fieldsTable->currentIndex();
    if (!index.isValid()) {
        return;
    }
    const auto field = model_->at(index.row());

    if (GENERATOR_OPTIONS.contains(field->type().ordinal())) {
        const auto &options = Settings::getPasswordOptions(GENERATOR_OPTIONS[field->type().ordinal()]);
        auto password = pwdgen::generate(*options.get());
        model_->setFieldValue(index.row(), QString::fromStdString(password));
    }
}

void CardEditDialog::fieldTableContextMenuRequested(QPoint pos) {
    auto index = ui->fieldsTable->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    fieldTableContextMenu_->popup(ui->fieldsTable->viewport()->mapToGlobal(pos));
}

void CardEditDialog::fieldTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &) {
    if (!current.isValid()) {
        return;
    }
    const auto field = model_->at(current.row());
    fieldUpAction_->setEnabled(current.row() != 0);
    fieldDownAction_->setEnabled(current.row() != model_->rowCount() - 1);
    fieldGenerateAction_->setEnabled(GENERATOR_OPTIONS.contains(field->type().ordinal()));
}
