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

    void test_add_task();
    void test_modify_task();
    void test_remove_task();

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

void Test::test_add_task()
{
    auto newTask = new Task();
    newTask->setDescription("test");
    newTask->setExecutorGroup(SystemUserType::WORKER);
    Database::instance()->saveTask(newTask);
    Q_ASSERT(Database::instance()->getTaskById(newTask->id())->id() == newTask->id());
}

void Test::test_modify_task()
{
    auto task = Database::instance()->tasks().last();
    task->setDone(true);
    Q_ASSERT(Database::instance()->getTaskById(task->id())->done() == true);
}

void Test::test_remove_task()
{
    auto taskId = Database::instance()->tasks().last()->id();
    Database::instance()->removeTaskById(taskId);
    Q_ASSERT(Database::instance()->tasks().last()->id() != taskId);
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
