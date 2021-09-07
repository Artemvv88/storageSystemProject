#include "database.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Database::instance()->readDB();

    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    auto exitCode = a.exec();

    Database::instance()->writeDB();

    return exitCode;
}
