#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>

#include "database.h"
#include "loginwindow.h"
#include "systemuser.h"


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

private slots:
    void on_addUserBtn_clicked();
    void on_addRackBtn_clicked();
    void on_addProductBtn_clicked();
    void on_markCompletedButton_clicked();
    void on_addTask_clicked();
    void on_usersTable_doubleClicked(const QModelIndex &index);
    void on_racksTable_doubleClicked(const QModelIndex &index);
    void on_productsTable_doubleClicked(const QModelIndex &index);
    void on_tasksTable_doubleClicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
