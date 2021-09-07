#include "registrationwindow.h"
#include "ui_registrationwindow.h"

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    if (Database::instance()->users().length() == 0) {
        QMessageBox::information(this, "Информация", "Т.к. в системе нет пользователей, текущий регистрируемый пользователь будет использован в качестве аккаунта администратора.");
        ui->accountTypeDropdown->setEnabled(false);
    }
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::closeEvent(QCloseEvent *event)
{
    if (qobject_cast<MainWindow*>(parent()) == nullptr) {
        auto w = new LoginWindow();
        w->show();
    }
    event->accept();
}

void RegistrationWindow::on_registerBtn_clicked()
{
    if (ui->loginInput->text().isEmpty() || ui->passwordInput->text().isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Проверьте поля формы!");
        return;
    }

    auto user = Database::instance()->registerUser(
                    ui->loginInput->text(),
                    ui->passwordInput->text(),
                    (SystemUserType) ui->accountTypeDropdown->currentIndex()
                );

    if (user == nullptr) {
        QMessageBox::critical(this, "Ошибка", "Пользователь с таким логином уже существует");
        return;
    }

    close();
}
