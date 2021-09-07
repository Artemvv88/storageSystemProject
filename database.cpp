#include "database.h"

Database *Database::_instance = nullptr;

Database::Database()
{

}

void Database::readDB()
{
    {
        QFile file(Database::USERS_FILENAME);
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);

        quint32 usersCount = 0;
        in >> usersCount;
        for (quint32 i = 0; i < usersCount; i++) {
            auto user = new SystemUser();
            in >> user->_id;
            in >> user->_login;
            in >> user->_passwordHash;
            in >> user->_userType;
            _users.append(user);
        }

        file.close();
    }
    {
        QFile file(Database::TASKS_FILENAME);
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);

        quint32 tasksCount = 0;
        in >> tasksCount;
        for (quint32 i = 0; i < tasksCount; i++) {
            auto task = new Task();
            in >> task->_id;
            in >> task->_description;
            in >> task->_executorGroup;
            in >> task->_done;
            _tasks.append(task);
        }

        file.close();
    }
    {
        QFile file(Database::RACKS_FILENAME);
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);

        quint32 racksCount = 0;
        in >> racksCount;
        for (quint32 i = 0; i < racksCount; i++) {
            auto rack = new Rack();
            in >> rack->_id;
            in >> rack->_storagePosition;
            in >> rack->_capacity;
            quint32 productsCount = 0;
            in >> productsCount;
            for (quint32 j = 0; j < productsCount; j++) {
                auto product = new Product();
                in >> product->_id;
                in >> product->_title;
                in >> product->_info;
                quint32 flowCount = 0;
                in >> flowCount;
                for (quint32 k = 0; k < flowCount; k++) {
                    int flowAmount = 0;
                    in >> flowAmount;
                    product->_flow.append(flowAmount);
                }
                rack->products().append(product);
            }
            _racks.append(rack);
        }

        file.close();
    }
}

void Database::writeDB()
{
    {
        QFile file(Database::USERS_FILENAME);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);

        out << _users.length();
        for (auto user : _users) {
            out << user->id();
            out << user->login();
            out << user->passwordHash();
            out << user->userType();
        }

        file.close();
    }
    {
        QFile file(Database::TASKS_FILENAME);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);

        out << _tasks.length();
        for (auto task : _tasks) {
            out << task->id();
            out << task->description();
            out << task->executorGroup();
            out << task->done();
        }

        file.close();
    }
    {
        QFile file(Database::RACKS_FILENAME);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);

        out << _racks.length();
        for (auto rack : _racks) {
            out << rack->id();
            out << rack->storagePosition();
            out << rack->capacity();
            out << rack->products().length();
            for (auto product : rack->products()) {
                out << product->id();
                out << product->title();
                out << product->info();
                out << product->flow().length();
                for (auto flowAmount : product->flow()) {
                    out << flowAmount;
                }
            }
        }

        file.close();
    }
}

Database *Database::instance()
{
    if (_instance == nullptr) {
        _instance = new Database();
    }
    return _instance;
}

QVector<SystemUser *> Database::users() const
{
    return _users;
}

QVector<Task *> Database::tasks() const
{
    return _tasks;
}

QVector<Rack *> Database::racks() const
{
    return _racks;
}

SystemUser *Database::getUserById(UserID userId)
{
    for (auto _user : _users) {
        if (_user->id() == userId) {
            return _user;
        }
    }

    return nullptr;
}

SystemUser *Database::getUserByLogin(const QString &login)
{
    for (auto _user : _users) {
        if (_user->login() == login) {
            return _user;
        }
    }

    return nullptr;
}

SystemUser *Database::getUserByLoginAndPassword(const QString &login, const QString &password)
{
    auto passwordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    auto user = getUserByLogin(login);
    if (user == nullptr || user->passwordHash() != passwordHash) {
        user = nullptr;
    }

    return user;
}

SystemUser *Database::registerUser(const QString &login, const QString &password, SystemUserType userType)
{
    if (getUserByLogin(login) != nullptr) {
        return nullptr;
    }

    auto user = new SystemUser();
    user->_id = _users.length();
    user->_login = login;
    user->_passwordHash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    user->_userType = userType;
    _users.append(user);
    return user;
}
