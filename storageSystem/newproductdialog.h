#ifndef NEWPRODUCTDIALOG_H
#define NEWPRODUCTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QString>

#include "product.h"
#include "database.h"


namespace Ui {
class NewProductDialog;
}

class NewProductDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NewProductDialog *ui;

    bool isNew = true;
    Product *newProduct = nullptr;
    Rack *parentRack = nullptr;

public:
    explicit NewProductDialog(QWidget *parent = nullptr);
    ~NewProductDialog();

    Product *getProduct();
    void setProduct(Product *product, Rack *parentRack, bool isProductNew=true);

public slots:
    void accept();
};

#endif // NEWPRODUCTDIALOG_H
