#include "newtaskdialog.h"
#include "ui_newtaskdialog.h"

NewTaskDialog::NewTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog)
{
    ui->setupUi(this);
}

NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}

Task *NewTaskDialog::getTask()
{
    return newTask;
}

void NewTaskDialog::setTask(Task *task, bool isTaskNew, bool isStoragekeeper)
{
    newTask = task;
    isNew = isTaskNew;
    if (isNew) {
        ui->idLabel->setText("Будет присвоен после сохранения");
    } else {
        ui->idLabel->setText(QString::number(task->id()));
        ui->descriptionInput->setPlainText(task->description());
        ui->userGroupDropdown->setCurrentIndex((int)task->executorGroup() - 1);
    }
    if (isStoragekeeper) {
        ui->userGroupDropdown->setCurrentIndex(1);
        ui->userGroupDropdown->setEnabled(false);
    }
}

void NewTaskDialog::accept()
{
    QString errorMessage;

    if (ui->descriptionInput->toPlainText().isEmpty()) {
        errorMessage += "Описание задачи не может быть пустым. \n";
    }
    errorMessage = errorMessage.trimmed();
    if (!errorMessage.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", errorMessage);
        return;
    }

    newTask->setDescription(ui->descriptionInput->toPlainText());
    newTask->setExecutorGroup((SystemUserType)(ui->userGroupDropdown->currentIndex() + 1));

    if (isNew) {
        if (Database::instance()->tasks().length() > 0) {
            newTask->_id = Database::instance()->tasks().last()->id() + 1;
        } else {
            newTask->_id = 0;
        }
        Database::instance()->saveTask(newTask);
    }

    QDialog::accept();
}
