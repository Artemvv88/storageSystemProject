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

Rack *NewRackDialog::getRack()
{
    return newRack;
}

void NewRackDialog::setRack(Rack *rack, bool isRackNew)
{
    newRack = rack;
    isNew = isRackNew;
    if (isNew) {
        ui->idLabel->setText("Будет присвоен после сохранения");
    } else {
        ui->idLabel->setText(QString::number(rack->id()));
        ui->capacitySpinner->setValue(rack->capacity());
        ui->positionSpinner->setValue(rack->storagePosition());
    }
}

void NewRackDialog::accept()
{
    QString errorMessage;
    if (ui->capacitySpinner->value() <= 0) {
        errorMessage += "Объём не может быть меньше либо равен нулю. \n";
    }
    int spaceUsed = 0;
    for (auto p : newRack->products()) {
        spaceUsed += p->size();
    }
    if (ui->capacitySpinner->value() < spaceUsed) {
        errorMessage += "Объём не может быть меньше уже занятого пространства. \n";
    }
    if (Database::instance()->spaceOccupied(ui->positionSpinner->value())) {
        errorMessage += "Данная позиция уже занята. \n";
    }
    errorMessage = errorMessage.trimmed();
    if (!errorMessage.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", errorMessage);
        return;
    }

    newRack->setCapacity(ui->capacitySpinner->value());
    newRack->setStoragePosition(ui->positionSpinner->value());

    if (isNew) {
        if (Database::instance()->racks().length() > 0) {
            newRack->_id = Database::instance()->racks().last()->id() + 1;
        } else {
            newRack->_id = 0;
        }
        Database::instance()->saveRack(newRack);
    }

    QDialog::accept();
}
