#ifndef TASK_H
#define TASK_H

#include <QtGlobal>
#include <QString>
#include <QVector>

#include "systemuser.h"


typedef quint32 TaskID;

class Task
{
private:
    TaskID _id;
    QString _description;
    SystemUserType _executorGroup;
    bool _done = false;

public:
    Task();

    TaskID id() const;
    QString description() const;
    void setDescription(const QString &description);
    SystemUserType executorGroup() const;
    void setExecutorGroup(const SystemUserType &executorGroup);
    bool done() const;
    void setDone(bool done);

    friend class Database;
};

#endif // TASK_H
