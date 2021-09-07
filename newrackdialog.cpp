#include "newrackdialog.h"
#include "ui_newrackdialog.h"

NewRackDialog::NewRackDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRackDialog)
{
    ui->setupUi(this);
}

NewRackDialog::~NewRackDialog()
{
    delete ui;
}
