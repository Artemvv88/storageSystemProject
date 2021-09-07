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

Product *NewProductDialog::getProduct()
{
    return newProduct;
}

void NewProductDialog::setProduct(Product *product, Rack* parentRack, bool isProductNew)
{
    newProduct = product;
    isNew = isProductNew;
    this->parentRack = parentRack;
    if (isNew) {
        ui->idLabel->setText("Будет присвоен после сохранения");
    } else {
        ui->idLabel->setText(QString::number(product->id()));
        ui->titleInput->setText(product->title());
        ui->sizeSpinner->setValue(product->size());
        ui->descriptionInput->setPlainText(product->info());
    }
}

void NewProductDialog::accept()
{
    QString errorMessage;
    if (ui->titleInput->text().isEmpty()) {
        errorMessage += "Название не может быть пустым. \n";
    }
    if (ui->sizeSpinner->value() <= 0) {
        errorMessage += "Объём не может быть меньше либо равен нулю. \n";
    }
    auto delta = ui->sizeSpinner->value() - newProduct->size();
    int spaceUsed = 0;
    for (auto p : parentRack->products()) {
        spaceUsed += p->size();
    }
    if (spaceUsed + delta > parentRack->capacity()) {
        errorMessage += "Суммарный объём продуктов на стеллаже превысит вместимость стеллажа. \n";
    }
    errorMessage = errorMessage.trimmed();
    if (!errorMessage.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", errorMessage);
        return;
    }

    newProduct->setTitle(ui->titleInput->text());
    newProduct->setInfo(ui->descriptionInput->toPlainText());
    newProduct->setSize(ui->sizeSpinner->value());

    if (isNew) {
        if (parentRack->products().length() > 0) {
            newProduct->_id = parentRack->products().last()->id() + 1;
        } else {
            newProduct->_id = 0;
        }
    }

    QDialog::accept();
}
