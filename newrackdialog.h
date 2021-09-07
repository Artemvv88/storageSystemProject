#ifndef NEWRACKDIALOG_H
#define NEWRACKDIALOG_H

#include <QDialog>

namespace Ui {
class NewRackDialog;
}

class NewRackDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewRackDialog(QWidget *parent = nullptr);
    ~NewRackDialog();

private:
    Ui::NewRackDialog *ui;
};

#endif // NEWRACKDIALOG_H
