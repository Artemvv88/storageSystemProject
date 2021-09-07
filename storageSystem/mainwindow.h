#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>

#include "database.h"
#include "systemuser.h"
#include "rack.h"
#include "task.h"

#include "loginwindow.h"
#include "registrationwindow.h"
#include "newrackdialog.h"
#include "newproductdialog.h"
#include "newtaskdialog.h"
#include "productflowdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    SystemUser *_user;

    void closeEvent(QCloseEvent *event);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUser(SystemUser *user);

signals:
    void needUiUpdate();

public slots:
    void updateUi();

private slots:
    void on_addUserBtn_clicked();
    void on_addRackBtn_clicked();
    void on_addProductBtn_clicked();
    void on_markCompletedButton_clicked();
    void on_addTask_clicked();
    void on_usersTable_doubleClicked(const QModelIndex&);
    void on_racksTable_clicked(const QModelIndex&);
    void on_racksTable_doubleClicked(const QModelIndex&);
    void on_productsTable_doubleClicked(const QModelIndex&);
    void on_tasksTable_doubleClicked(const QModelIndex&);
    void on_lookupFlowBtn_clicked();
    void on_removeUserBtn_clicked();
    void on_removeRackBtn_clicked();
    void on_removeProductBtn_clicked();
    void on_removeTaskBtn_clicked();
};

#endif // MAINWINDOW_H
