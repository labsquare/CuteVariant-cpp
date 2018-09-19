#include <QtTest>
#include "cutevariant.h"


class TestSample : public QObject
{
    Q_OBJECT

public:
    TestSample();
    ~TestSample();

private slots:
    void test_case1();

};

TestSample::TestSample()
{

}

TestSample::~TestSample()
{

}

void TestSample::test_case1()
{
    qDebug()<<"test sacha";
    QVERIFY(true);
}

QTEST_APPLESS_MAIN(TestSample)

#include "tst_testsample.moc"
