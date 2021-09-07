#ifndef DATABASE_H
#define DATABASE_H

#include <QtGlobal>
#include <QVector>
#include <QString>
#include <QFile>
#include <QDataStream>

#include "systemuser.h"
#include "task.h"
#include "rack.h"
#include "product.h"


class Database
{
private:
    static Database *_instance;

    const QString USERS_FILENAME = "users.bin";
    const QString TASKS_FILENAME = "tasks.bin";
    const QString RACKS_FILENAME = "racks.bin";

    QVector<SystemUser*> _users;
    QVector<Task*> _tasks;
    QVector<Rack*> _racks;

public:
    Database();

    void readDB();
    void writeDB();

    static Database *instance();

    QVector<SystemUser *> users() const;
    QVector<Task *> tasks() const;
    QVector<Rack *> racks() const;
};

#endif // DATABASE_H