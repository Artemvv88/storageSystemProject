#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "registrationwindow.h"
#include "mainwindow.h"
#include "systemuser.h"
#include "database.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::LoginWindow *ui;

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_logInBtn_clicked();
    void on_registerBtn_clicked();
};
#endif // LOGINWINDOW_H
