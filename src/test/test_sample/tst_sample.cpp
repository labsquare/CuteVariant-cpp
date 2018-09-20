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

    void toUpper_data();
    void toUpper();

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
    QCOMPARE(SampleDataMapper::i()->list().first().name(),"sacha");

}

void TestSample::toUpper_data()
{
      QTest::addColumn<QString>("string");
      QTest::addColumn<QString>("result");

      QTest::newRow("all lower") << "hello" << "HELLO";
      QTest::newRow("mixed")     << "Hello" << "HELLO";
      QTest::newRow("all upper") << "HELLO" << "HELLO";
}

void TestSample::toUpper()
{
       QFETCH(QString, string);
       QFETCH(QString, result);

       QCOMPARE(string.toUpper(), result);
}



QTEST_APPLESS_MAIN(TestSample)

#include "tst_sample.moc"
