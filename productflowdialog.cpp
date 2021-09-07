#include "productflowdialog.h"
#include "ui_productflowdialog.h"

ProductFlowDialog::ProductFlowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductFlowDialog)
{
    ui->setupUi(this);
}

ProductFlowDialog::~ProductFlowDialog()
{
    delete ui;
}

void ProductFlowDialog::drawList()
{
    for (auto flowItem : product->flow()) {
        ui->historyList->addItem(tr("Дата: %1\nПриход: %2").arg(flowItem.first.toString("dd.MM.yyyy")).arg(flowItem.second));
    }
}

void ProductFlowDialog::setProduct(Product *value)
{
    product = value;
    drawList();
}

void ProductFlowDialog::on_addBtn_clicked()
{
    if (ui->amountSpinner->value() == 0) {
        QMessageBox::critical(this, "Ошибка", "Кол-во должно быть не равно нулю!");
        return;
    }

    product->addFlowItem(ui->amountSpinner->value());

    drawList();
}

void ProductFlowDialog::on_deleteBtn_clicked()
{
    auto indexes = ui->historyList->selectionModel()->selectedIndexes();
    for (int i = 0; i < indexes.length(); i++) {
        auto index = indexes.at(i).row();
        product->removeFlowItemAt(index);
    }

    drawList();
}
