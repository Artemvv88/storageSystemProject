#include <QtTest>

#include "../storageSystem/database.h"

class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();

private slots:
    void test_register_user();
    void test_cannot_register_same_user();
    void test_modify_user();
    void test_remove_user();

};

Test::Test()
{

}

Test::~Test()
{

}

void Test::test_register_user()
{
    auto regUser = Database::instance()->registerUser("test", "test", SystemUserType::ADMINISTRATOR);
    Q_ASSERT(Database::instance()->getUserByLogin("test")->id() == regUser->id());
}

void Test::test_cannot_register_same_user()
{

    auto regUser = Database::instance()->registerUser("test", "test", SystemUserType::ADMINISTRATOR);
    Q_ASSERT(regUser == nullptr);
}

void Test::test_modify_user()
{
    Database::instance()->getUserByLogin("test")->setUserType(SystemUserType::WORKER);
    Q_ASSERT(Database::instance()->getUserByLogin("test")->userType() == SystemUserType::WORKER);
}

void Test::test_remove_user()
{
    Database::instance()->removeUserById(Database::instance()->getUserByLogin("test")->id());
    Q_ASSERT(Database::instance()->getUserByLogin("test") == nullptr);
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
