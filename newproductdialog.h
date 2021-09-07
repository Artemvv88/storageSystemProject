#ifndef NEWPRODUCTDIALOG_H
#define NEWPRODUCTDIALOG_H

#include <QDialog>

namespace Ui {
class NewProductDialog;
}

class NewProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProductDialog(QWidget *parent = nullptr);
    ~NewProductDialog();

private:
    Ui::NewProductDialog *ui;
};

#endif // NEWPRODUCTDIALOG_H
