//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
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
    : QDialog(parent), ui(make_unique<Ui::CardEditDialog>()), model_{make_unique<EditFieldListModel>(this)},
      fieldAddAction_{tr("Add"), this}, fieldDeleteAction_{tr("Delete"), this}, fieldUpAction_{tr("Up"), this},
      fieldDownAction_{tr("Down"), this}, fieldGenerateAction_(tr("Generate"), this)

{
    ui->setupUi(this);

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
    card_ = std::shared_ptr<Card>(new Card(card));

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
    auto pictureIndex = QtHelpers::indexOfData(*ui->pictureComboBox, card.picture().ordinal());
    if (pictureIndex != -1) {
        ui->pictureComboBox->setCurrentIndex(pictureIndex);
    }
}

void CardEditDialog::setupFieldTable() {
    auto t = ui->fieldsTable;

    QtHelpers::addActions(
        t, {&fieldAddAction_, &fieldDeleteAction_, &fieldGenerateAction_, &fieldUpAction_, &fieldDownAction_});

    t->setModel(model_.get());
    t->setEditTriggers(QAbstractItemView::DoubleClicked);
    t->setItemDelegateForColumn(EditFieldListModel::FIELD_TABLE_TYPE_COLUMN, new FieldValueEditDelegate());
    t->setItemDelegateForColumn(EditFieldListModel::FIELD_TABLE_VALUE_COLUMN, new FieldValueEditDelegate());

    connect(t->selectionModel(), &QItemSelectionModel::currentRowChanged, this,
            &CardEditDialog::fieldTableCurrentRowChanged);

    auto header = t->horizontalHeader();
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_NAME_COLUMN, QHeaderView::Stretch);
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_TYPE_COLUMN, QHeaderView::Stretch);
    header->setSectionResizeMode(EditFieldListModel::FIELD_TABLE_VALUE_COLUMN, QHeaderView::Stretch);
}

void CardEditDialog::setupFieldTableContextMenu() {
    fieldAddAction_.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    fieldDeleteAction_.setShortcut(QKeySequence(Qt::Key_Delete));
    fieldGenerateAction_.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));
    fieldUpAction_.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Up));
    fieldDownAction_.setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Down));

    QtHelpers::addActions(&fieldTableContextMenu_,
                          {&fieldAddAction_, &fieldDeleteAction_, nullptr, &fieldGenerateAction_, nullptr,
                           &fieldUpAction_, &fieldDownAction_});

    connect(&fieldAddAction_, &QAction::triggered, this, &CardEditDialog::onAddField);
    connect(&fieldDeleteAction_, &QAction::triggered, this, &CardEditDialog::onDeleteField);
    connect(&fieldUpAction_, &QAction::triggered, this, &CardEditDialog::onFieldUp);
    connect(&fieldDownAction_, &QAction::triggered, this, &CardEditDialog::onFieldDown);
    connect(&fieldGenerateAction_, &QAction::triggered, this, &CardEditDialog::onGenerate);

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

        card_->setModified(TimeUtil::currentTimeMillis());
        card_->setName(newName);
        card_->setFields(model_->fields());
        // picture
        auto pictureOrdinal = ui->pictureComboBox->currentData().toUInt();
        card_->setPicture(Picture::valueOf(pictureOrdinal));
        // note
        card_->setNote(ui->notesEditor->toPlainText());
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
    auto field = model_->at(index.row());

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
    auto field = model_->at(index.row());

    if (GENERATOR_OPTIONS.contains(field->type().ordinal())) {
        const auto &options = Settings::getPasswordOptions(GENERATOR_OPTIONS[field->type().ordinal()]);
        auto password = pwdgen::generate(options);
        model_->setFieldValue(index.row(), field, QString::fromStdString(password));
    }
}

void CardEditDialog::fieldTableContextMenuRequested(QPoint pos) {
    auto index = ui->fieldsTable->indexAt(pos);
    if (!index.isValid()) {
        return;
    }
    fieldTableContextMenu_.popup(ui->fieldsTable->viewport()->mapToGlobal(pos));
}

void CardEditDialog::fieldTableCurrentRowChanged(const QModelIndex &current, const QModelIndex &) {
    if (!current.isValid()) {
        return;
    }
    auto field = model_->at(current.row());
    fieldUpAction_.setEnabled(current.row() != 0);
    fieldDownAction_.setEnabled(current.row() != model_->rowCount() - 1);
    fieldGenerateAction_.setEnabled(GENERATOR_OPTIONS.contains(field->type().ordinal()));
}
