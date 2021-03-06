#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>

#include "database.h"
#include "mainwindow.h"
#include "loginwindow.h"


namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::RegistrationWindow *ui;

    SystemUser *user = nullptr;

    void closeEvent(QCloseEvent *event);

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

    void setUser(SystemUser *user);

private slots:
    void on_registerBtn_clicked();
};

#endif // REGISTRATIONWINDOW_H
