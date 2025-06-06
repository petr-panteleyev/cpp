//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "importrecordtablemodel.h"
#include "card.h"
#include "settings.h"
#include "translations.h"
#include <QDate>

static std::unordered_map<ImportAction, Settings::Color> ACTION_COLORS{
    {ImportAction::ADD, Settings::Color::ImportAdd},
    {ImportAction::REPLACE, Settings::Color::ImportReplace},
    {ImportAction::DELETE, Settings::Color::ImportDelete},
    {ImportAction::RESTORE, Settings::Color::ImportRestore},
};

static std::vector<unsigned> COLUMN_ALIGNMENT{Qt::AlignLeft, Qt::AlignCenter, Qt::AlignCenter};

static const QColor WHITE = QColor::fromRgb(255, 255, 255);

ImportRecordTableModel::ImportRecordTableModel(QObject *parent) : QAbstractItemModel{parent} {
}

ImportRecordTableModel::~ImportRecordTableModel() {
}

QVariant ImportRecordTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const auto &record = records_.at(index.row());

    if (role == Qt::BackgroundRole) {
        return !ACTION_COLORS.contains(record.action()) || !record.approved()
                   ? WHITE
                   : Settings::getColor(ACTION_COLORS[record.action()]);
    } else if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case COLUMN_TITLE: return record.cardToImport()->name();
            case COLUMN_UPDATED: {
                auto dateTime = QDateTime::fromMSecsSinceEpoch(record.cardToImport()->modified());
                return dateTime.toString("dd.MM.yyyy HH:mm:ss");
            }
            case COLUMN_ACTION: return Translations::translate(record.effectiveAction());
        }
    } else if (role == Qt::TextAlignmentRole) {
        return COLUMN_ALIGNMENT.at(index.column());
    }

    return QVariant();
}

void ImportRecordTableModel::toggleApproval(int row) {
    auto &record = records_.at(row);
    record.toggleApproval();
    auto updatedIndex = index(row, COLUMN_ACTION);
    emit dataChanged(updatedIndex, updatedIndex, {Qt::DisplayRole});
}
