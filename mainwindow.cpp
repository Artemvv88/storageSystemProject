#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::needUiUpdate, this, &MainWindow::updateUi);
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

void MainWindow::updateUi()
{

}

void MainWindow::on_addUserBtn_clicked()
{
    auto w = new RegistrationWindow(this);
    w->show();
    delete w;

    emit needUiUpdate();
}

void MainWindow::on_addRackBtn_clicked()
{
    NewRackDialog d(this);
    if (d.exec() != QDialog::Accepted) {
        return;
    }

    emit needUiUpdate();
}

void MainWindow::on_addProductBtn_clicked()
{
    auto selectedRows = ui->racksTable->selectionModel()->selectedRows();
    if (selectedRows.length() != 1) {
        return;
    }

    RackID rid = selectedRows[0].data().toUInt();
    auto rack = Database::instance()->getRackById(rid);
    if (rack == nullptr) {
        QMessageBox::information(this, "Информация", "С начала нужно выбрать стеллаж в списке");
        return;
    }

    NewProductDialog d(this);
    d.setProduct(new Product(), rack, true);
    if (d.exec() != QDialog::Accepted) {
        return;
    }

    emit needUiUpdate();
}

void MainWindow::on_markCompletedButton_clicked()
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
