#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabHost->setCurrentIndex(0);

    connect(this, &MainWindow::needUiUpdate, this, &MainWindow::updateUi);

    emit needUiUpdate();
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
    ui->userName->setText(_user->login());
    if (_user->userType() != SystemUserType::ADMINISTRATOR) {
        ui->tabHost->removeTab(0); // Users tab
        ui->addRackBtn->hide();
        if (_user->userType() != SystemUserType::STOREKEEPER) {
            ui->addProductBtn->hide();
            ui->addTask->hide();
            ui->markCompletedButton->hide();
        }
    }
}

void MainWindow::updateUi()
{
    {
        ui->usersTable->setRowCount(0);
        for (auto user : Database::instance()->users()) {
            int rowid = ui->usersTable->rowCount();
            ui->usersTable->insertRow(rowid);
            ui->usersTable->setItem(rowid, 0, new QTableWidgetItem(QString::number(user->id())));
            ui->usersTable->setItem(rowid, 1, new QTableWidgetItem(user->login()));
            QString userRole;
            switch (user->userType()) {
                default:
                case SystemUserType::ERROR:
                    userRole = "Ошибка";
                    break;
                case SystemUserType::ADMINISTRATOR:
                    userRole = "Администратор";
                    break;
                case SystemUserType::STOREKEEPER:
                    userRole = "Кладовщик";
                    break;
                case SystemUserType::WORKER:
                    userRole = "Рабочий";
                    break;
            }
            ui->usersTable->setItem(rowid, 2, new QTableWidgetItem(userRole));
        }
        ui->usersTable->resizeRowsToContents();
    }
    {
        ui->productsTable->setRowCount(0);
        ui->racksTable->setRowCount(0);
        for (auto rack : Database::instance()->racks()) {
            int rowid = ui->racksTable->rowCount();
            ui->racksTable->insertRow(rowid);
            ui->racksTable->setItem(rowid, 0, new QTableWidgetItem(QString::number(rack->id())));
            ui->racksTable->setItem(rowid, 1, new QTableWidgetItem(QString::number(rack->storagePosition())));
            ui->racksTable->setItem(rowid, 2, new QTableWidgetItem(QString::number(rack->capacity())));
            int usedSpace = 0;
            for (auto product : rack->products()) {
                usedSpace += product->size();
            }
            ui->racksTable->setItem(rowid, 3, new QTableWidgetItem(QString::number(rack->capacity() - usedSpace)));
        }
        ui->racksTable->resizeRowsToContents();
    }
    {
        ui->tasksTable->setRowCount(0);
        for (auto task : Database::instance()->tasks()) {
            int rowid = ui->tasksTable->rowCount();
            ui->tasksTable->insertRow(rowid);
            ui->tasksTable->setItem(rowid, 0, new QTableWidgetItem(QString::number(task->id())));
            ui->tasksTable->setItem(rowid, 1, new QTableWidgetItem(task->description()));
            QString groupRole;
            switch (task->executorGroup()) {
                default:
                case SystemUserType::ERROR:
                    groupRole = "Ошибка";
                    break;
                case SystemUserType::ADMINISTRATOR:
                    groupRole = "Администратор";
                    break;
                case SystemUserType::STOREKEEPER:
                    groupRole = "Кладовщик";
                    break;
                case SystemUserType::WORKER:
                    groupRole = "Рабочий";
                    break;
            }
            ui->tasksTable->setItem(rowid, 2, new QTableWidgetItem(groupRole));
            ui->tasksTable->setItem(rowid, 3, new QTableWidgetItem(task->done()? "Да" : "Нет"));
        }
        ui->tasksTable->resizeRowsToContents();
    }
}

void MainWindow::on_addUserBtn_clicked()
{
    RegistrationWindow w(this);
    w.exec();

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
    rack->addProduct(p);

    on_racksTable_clicked(QModelIndex());
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

void MainWindow::on_usersTable_doubleClicked(const QModelIndex&)
{
    auto item = ui->usersTable->selectionModel()->selectedRows()[0];
    UserID uid = item.data(Qt::DisplayRole).toUInt();
    auto user = Database::instance()->getUserById(uid);
    if (user == nullptr) {
        QMessageBox::critical(this, "Ошибка", "Выбран несуществующий пользовватель! Обратитесь к администратору.");
        return;
    }
    if (user->id() == _user->id()) {
        QMessageBox::critical(this, "Ошибка", "Нельзя редактировать собственный аккаунт!");
        return;
    }

    RegistrationWindow w(this);
    w.setUser(user);
    w.exec();

    emit needUiUpdate();
}

void MainWindow::on_racksTable_clicked(const QModelIndex&)
{
    auto item = ui->racksTable->selectionModel()->selectedRows()[0];
    RackID rid = item.data(Qt::DisplayRole).toUInt();
    auto rack = Database::instance()->getRackById(rid);
    if (rack == nullptr) {
        QMessageBox::critical(this, "Ошибка", "Выбран несуществующий стеллаж! Обратитесь к администратору.");
        return;
    }

    ui->productsTable->setRowCount(0);
    for (auto product : rack->products()) {
        int rowid = ui->productsTable->rowCount();
        ui->productsTable->insertRow(rowid);
        ui->productsTable->setItem(rowid, 0, new QTableWidgetItem(QString::number(product->id())));
        ui->productsTable->setItem(rowid, 1, new QTableWidgetItem(product->title()));
        ui->productsTable->setItem(rowid, 2, new QTableWidgetItem(product->info()));
        ui->productsTable->setItem(rowid, 3, new QTableWidgetItem(product->size()));
    }
    ui->productsTable->resizeRowsToContents();
}

void MainWindow::on_racksTable_doubleClicked(const QModelIndex&)
{
    if (_user->userType() != SystemUserType::ADMINISTRATOR) return;

    auto item = ui->racksTable->selectionModel()->selectedRows()[0];
    RackID rid = item.data(Qt::DisplayRole).toUInt();
    auto rack = Database::instance()->getRackById(rid);
    if (rack == nullptr) {
        QMessageBox::critical(this, "Ошибка", "Выбран несуществующий стеллаж! Обратитесь к администратору.");
        return;
    }

    NewRackDialog d(this);
    d.setRack(rack, false);
    d.exec();

    emit needUiUpdate();
}

void MainWindow::on_productsTable_doubleClicked(const QModelIndex&)
{
    if (_user->userType() == SystemUserType::WORKER) return;

    Rack *rack = nullptr;
    {
        auto item = ui->racksTable->selectionModel()->selectedRows()[0];
        RackID rid = item.data(Qt::DisplayRole).toUInt();
        rack = Database::instance()->getRackById(rid);
        if (rack == nullptr) {
            QMessageBox::critical(this, "Ошибка", "Выбран несуществующий стеллаж! Обратитесь к администратору.");
            return;
        }
    }

    Product *product = nullptr;
    {
        auto item = ui->productsTable->selectionModel()->selectedRows()[0];
        ProductID pid = item.data(Qt::DisplayRole).toUInt();
        product = rack->getProductById(pid);
        if (product == nullptr) {
            QMessageBox::critical(this, "Ошибка", "Выбран несуществующий продукт! Обратитесь к администратору.");
            return;
        }
    }

    NewProductDialog d(this);
    d.setProduct(product, rack, false);
    d.exec();

    on_racksTable_clicked(QModelIndex());
}

void MainWindow::on_tasksTable_doubleClicked(const QModelIndex&)
{
    if (_user->userType() == SystemUserType::WORKER) return;


}

void MainWindow::on_lookupFlowBtn_clicked()
{

}
