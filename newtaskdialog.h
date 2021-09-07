#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QString>

#include "task.h"
#include "database.h"

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NewTaskDialog *ui;

    bool isNew = true;
    Task *newTask = nullptr;

public:
    explicit NewTaskDialog(QWidget *parent = nullptr);
    ~NewTaskDialog();

    Task *getTask();
    void setTask(Task *task, bool isTaskNew=true);

public slots:
    void accept();
};

#endif // NEWTASKDIALOG_H
