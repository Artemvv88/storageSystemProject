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
    auto r = new Rack();
    NewRackDialog d(this);
    d.setRack(r, true);
    if (d.exec() != QDialog::Accepted) {
        delete r;
        return;
    }

    emit needUiUpdate();
}

void MainWindow::on_addProductBtn_clicked()
{
    auto selectedRows = ui->racksTable->selectionModel()->selectedRows();
    if (selectedRows.length() != 1) {
        QMessageBox::information(this, "Информация", "Не выбран стеллаж из списка!");
        return;
    }

    RackID rid = selectedRows[0].data().toUInt();
    auto rack = Database::instance()->getRackById(rid);
    if (rack == nullptr) {
        QMessageBox::critical(this, "Ошибка", "Выбран несуществующий стеллаж! Обратитесь к администратору.");
        return;
    }

    auto p = new Product();
    NewProductDialog d(this);
    d.setProduct(p, rack, true);
    if (d.exec() != QDialog::Accepted) {
        delete p;
        return;
    }

    emit needUiUpdate();
}

void MainWindow::on_markCompletedButton_clicked()
{
    auto selectedRows = ui->tasksTable->selectionModel()->selectedRows();
    if (selectedRows.length() != 1) {
        QMessageBox::information(this, "Информация", "Не выбрана задача из списка!");
        return;
    }

    TaskID tid = selectedRows[0].data().toUInt();
    auto task = Database::instance()->getTaskById(tid);
    if (task == nullptr) {
        QMessageBox::critical(this, "Ошибка", "Выбран несуществующий стеллаж! Обратитесь к администратору.");
        return;
    }

    task->setDone(true);

    emit needUiUpdate();
}

void MainWindow::on_addTask_clicked()
{
    auto t = new Task();
    NewTaskDialog d(this);
    d.setTask(t, true);
    if (d.exec() != QDialog::Accepted) {
        delete t;
        return;
    }

    emit needUiUpdate();
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
