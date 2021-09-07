#include "newproductdialog.h"
#include "ui_newproductdialog.h"

NewProductDialog::NewProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProductDialog)
{
    ui->setupUi(this);
}

NewProductDialog::~NewProductDialog()
{
    delete ui;
}
