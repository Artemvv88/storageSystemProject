#include "task.h"

Task::Task()
{

}

TaskID Task::id() const
{
    return _id;
}

QString Task::description() const
{
    return _description;
}

void Task::setDescription(const QString &description)
{
    _description = description;
}

SystemUserType Task::executorGroup() const
{
    return _executorGroup;
}

void Task::setExecutorGroup(const SystemUserType &executorGroup)
{
    _executorGroup = executorGroup;
}
