#ifndef NEWRACKDIALOG_H
#define NEWRACKDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QString>

#include "rack.h"
#include "database.h"


namespace Ui {
class NewRackDialog;
}

class NewRackDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NewRackDialog *ui;

    bool isNew = true;
    Rack *newRack = nullptr;

public:
    explicit NewRackDialog(QWidget *parent = nullptr);
    ~NewRackDialog();

    Rack *getRack();
    void setRack(Rack *rack, bool isRackNew=true);

public slots:
    void accept();
};

#endif // NEWRACKDIALOG_H
