//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#pragma once

#include "importrecord.h"
#include <QDialog>
#include <memory>
#include <vector>

namespace Ui {
class ImportDialog;
}

class ImportRecordTableModel;

class ImportDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ImportDialog(QWidget *parent);
    ~ImportDialog();

    void setup(const std::vector<ImportRecord> &toImport);
    std::vector<ImportRecord> records() const;

  private:
    void setupTableView();
    void setupContextMenu();
    void onContextMenuRequested(QPoint pos);
    void onToggleApproval();
    void onContextMenuAboutToShow();

  private:
    const std::unique_ptr<Ui::ImportDialog> ui;

    ImportRecordTableModel *model_;
    QMenu *contextMenu_;
    QAction *actionToggleApproval_;
};
