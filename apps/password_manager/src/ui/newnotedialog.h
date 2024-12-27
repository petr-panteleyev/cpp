//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef NEWNOTEDIALOG_H
#define NEWNOTEDIALOG_H

#include <QDialog>
#include <memory>

namespace Ui {
class NewNoteDialog;
}

class Card;

class NewNoteDialog : public QDialog {
    Q_OBJECT

  public:
    explicit NewNoteDialog(QWidget *parent);
    ~NewNoteDialog();

    std::shared_ptr<Card> note() const;

  private:
    std::unique_ptr<Ui::NewNoteDialog> ui;
};

#endif // NEWNOTEDIALOG_H
