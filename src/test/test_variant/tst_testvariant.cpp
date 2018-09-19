#include <QtTest>

// add necessary includes here

class TestVariant : public QObject
{
    Q_OBJECT

public:
    TestVariant();
    ~TestVariant();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

TestVariant::TestVariant()
{

}

TestVariant::~TestVariant()
{

}

void TestVariant::initTestCase()
{

}

void TestVariant::cleanupTestCase()
{

}

void TestVariant::test_case1()
{

}

QTEST_APPLESS_MAIN(TestVariant)

#include "tst_testvariant.moc"
