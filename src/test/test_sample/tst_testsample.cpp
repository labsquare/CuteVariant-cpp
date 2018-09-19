#include <QtTest>
#include "cutevariant.h"
#include "sampledatamapper.h"
using namespace cvar;
class TestSample : public QObject
{
    Q_OBJECT

public:


private slots:
    void initTestCase();
    void cleanupTestCase();

    void testCreateSample();

};



void TestSample::initTestCase()
{
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant.db"));
    QVERIFY(SampleDataMapper::i()->createTable());
}

void TestSample::cleanupTestCase()
{
    cutevariant->closeDatabase();
}

void TestSample::testCreateSample()
{

    QVERIFY(SampleDataMapper::i()->insertOne({"sacha"}));
    QVERIFY(SampleDataMapper::i()->list().size() > 0);
    QVERIFY2(SampleDataMapper::i()->list().first().name() == "sacha" , "tess");

}



QTEST_APPLESS_MAIN(TestSample)

#include "tst_testsample.moc"
