#ifndef PRODUCTFLOWDIALOG_H
#define PRODUCTFLOWDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "product.h"

namespace Ui {
class ProductFlowDialog;
}

class ProductFlowDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::ProductFlowDialog *ui;

    Product *product;

    void drawList();

public:
    explicit ProductFlowDialog(QWidget *parent = nullptr);
    ~ProductFlowDialog();

    void setProduct(Product *value);

private slots:
    void on_addBtn_clicked();

    void on_deleteBtn_clicked();
};

#endif // PRODUCTFLOWDIALOG_H
