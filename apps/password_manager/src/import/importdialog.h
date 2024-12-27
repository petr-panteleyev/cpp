/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include "importrecord.h"
#include <QDialog>
#include <memory>

namespace Ui {
class ImportDialog;
}

class ImportRecordTableModel;

class ImportDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ImportDialog(QWidget *parent);
    ~ImportDialog();

    void setup(const std::vector<std::shared_ptr<ImportRecord>> &toImport);

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

#endif // IMPORTDIALOG_H
