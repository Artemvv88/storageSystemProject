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

    void test_add_rack();
    void test_modify_rack();
    void test_add_product();
    void test_modify_product();
    void test_remove_product();
    void test_remove_rack();

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
    int oldSize = Database::instance()->tasks().length();
    Database::instance()->removeTaskById(taskId);
    Q_ASSERT(Database::instance()->tasks().length() < oldSize);
}

void Test::test_add_rack()
{
    auto rack = new Rack();
    rack->setCapacity(200);
    rack->setStoragePosition(1);
    Database::instance()->saveRack(rack);
    Q_ASSERT(Database::instance()->racks().last()->id() == rack->id());
}

void Test::test_modify_rack()
{
    auto rackId = Database::instance()->racks().last()->id();
    Database::instance()->getRackById(rackId)->setStoragePosition(12);
    Q_ASSERT(Database::instance()->getRackById(rackId)->storagePosition() == 12);
}

void Test::test_add_product()
{
    auto rackId = Database::instance()->racks().last()->id();
    auto product = new Product();
    product->setInfo("test");
    product->setSize(12);
    product->setTitle("test");
    Database::instance()->getRackById(rackId)->addProduct(product);
    Q_ASSERT(Database::instance()->getRackById(rackId)->products().last()->id() == product->id());
}

void Test::test_modify_product()
{
    auto rackId = Database::instance()->racks().last()->id();
    auto productId = Database::instance()->getRackById(rackId)->products().last()->id();
    Database::instance()->getRackById(rackId)->getProductById(productId)->setTitle("newTitle");
    Q_ASSERT(Database::instance()->getRackById(rackId)->getProductById(productId)->title() == "newTitle");
}

void Test::test_remove_product()
{
    auto rackId = Database::instance()->racks().last()->id();
    auto productId = Database::instance()->getRackById(rackId)->products().last()->id();
    int oldSize = Database::instance()->getRackById(rackId)->products().length();
    Database::instance()->getRackById(rackId)->removeProductById(productId);
    Q_ASSERT(Database::instance()->getRackById(rackId)->products().length() < oldSize);
}

void Test::test_remove_rack()
{
    auto rackId = Database::instance()->racks().last()->id();
    int oldSize = Database::instance()->racks().length();
    Database::instance()->removeRackById(rackId);
    Q_ASSERT(Database::instance()->racks().length() < oldSize);
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
