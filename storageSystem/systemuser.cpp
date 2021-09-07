#include "systemuser.h"

void SystemUser::setLogin(const QString &login)
{
    _login = login;
}

void SystemUser::setUserType(const SystemUserType &userType)
{
    _userType = userType;
}

SystemUser::SystemUser()
{
    
}

UserID SystemUser::id() const
{
    return _id;
}

QString SystemUser::login() const
{
    return _login;
}

QString SystemUser::passwordHash() const
{
    return _passwordHash;
}

SystemUserType SystemUser::userType() const
{
    return _userType;
}
