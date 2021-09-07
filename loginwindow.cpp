#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_logInBtn_clicked()
{
    if (ui->loginInput->text().isEmpty() || ui->passwordInput->text().isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Проверьте поля формы!");
        return;
    }

    auto user = Database::instance()->getUserByLoginAndPassword(ui->loginInput->text(), ui->passwordInput->text());
    if (user == nullptr) {
        QMessageBox::critical(this, "Ошибка", "Пользователь с такой связкой логин-пароль не найден!");
        return;
    }

    auto w = new MainWindow();
    w->setUser(user);
    w->show();
    close();
}

void LoginWindow::on_registerBtn_clicked()
{
    auto w = new RegistrationWindow();
    w->show();
    close();
}
