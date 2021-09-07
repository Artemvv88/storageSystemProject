#include "registrationwindow.h"
#include "ui_registrationwindow.h"

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QDialog(parent),
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

void RegistrationWindow::setUser(SystemUser *user)
{
    this->user = user;
    ui->titleLabel->setText("Редактирование пользователя");
    ui->registerBtn->setText("Сохранить");
    ui->loginInput->setDisabled(true);
    ui->loginInput->setText(user->login());
    ui->accountTypeDropdown->setCurrentIndex((int)user->userType());
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

    if (user == nullptr) {
        if (qobject_cast<MainWindow*>(parent()) == nullptr && ui->accountTypeDropdown->currentIndex() == 0 && Database::instance()->users().length() > 0) {
            QMessageBox::critical(this, "Ошибка", "Только администратор может создавать других администраторов");
            return;
        }

        auto _user = Database::instance()->registerUser(
                        ui->loginInput->text(),
                        ui->passwordInput->text(),
                        (SystemUserType) ui->accountTypeDropdown->currentIndex()
                    );

        if (_user == nullptr) {
            QMessageBox::critical(this, "Ошибка", "Пользователь с таким логином уже существует");
            return;
        }
    } else {
        user->_passwordHash = QString(QCryptographicHash::hash(ui->passwordInput->text().toUtf8(), QCryptographicHash::Sha256).toHex());
        user->setUserType((SystemUserType) ui->accountTypeDropdown->currentIndex());
    }

    close();
}
