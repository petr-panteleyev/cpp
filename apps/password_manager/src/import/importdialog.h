/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include "importrecord.h"
#include "importrecordtablemodel.h"
#include <QDialog>
#include <QMenu>

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog {
    Q_OBJECT

  public:
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog();

    void setup(const ImportRecordVec &toImport);

  private:
    void setupTableView();
    void setupContextMenu();
    void onContextMenuRequested(QPoint pos);
    void onToggleApproval();
    void onContextMenuAboutToShow();

  private:
    Ui::ImportDialog *ui;

    ImportRecordTableModel model_;
    QAction                actionToggleApproval_;
    QMenu                  contextMenu_;
};

#endif // IMPORTDIALOG_H
