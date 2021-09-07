#ifndef SYSTEMUSER_H
#define SYSTEMUSER_H

#include <QtGlobal>
#include <QString>


enum class SystemUserType {
    ERROR, ADMINISTRATOR, STOREKEEPER, WORKER
};

typedef quint32 UserID;

class SystemUser
{
private:
    UserID _id;
    QString _login;
    QString _passwordHash;
    SystemUserType _userType;

public:
    SystemUser();

    UserID id() const;
    QString login() const;
    void setLogin(const QString &login);
    QString passwordHash() const;
    SystemUserType userType() const;
    void setUserType(const SystemUserType &userType);

    friend class Database;
};

#endif // SYSTEMUSER_H
