#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    auto w = new LoginWindow();
    w->show();
    event->accept();
}

void MainWindow::setUser(SystemUser *user)
{
    _user = user;
}

void MainWindow::on_addUserBtn_clicked()
{

}

void MainWindow::on_addRackBtn_clicked()
{

}

void MainWindow::on_addProductBtn_clicked()
{

}

void MainWindow::on_addTask_clicked()
{

}

void MainWindow::on_usersTable_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::on_racksTable_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::on_productsTable_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::on_tasksTable_doubleClicked(const QModelIndex &index)
{

}
