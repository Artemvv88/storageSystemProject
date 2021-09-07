#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUser(SystemUser *user);
};

#endif // MAINWINDOW_H
