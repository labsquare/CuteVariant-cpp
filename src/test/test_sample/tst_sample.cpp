#include <QtTest>
#include "cutevariant.h"
#include "sampledatamapper.h"

class Sample : public QObject
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



void Sample::initTestCase()
{
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant.db"));
    QVERIFY(cvar::SampleDataMapper::i()->createTable());
}

void Sample::cleanupTestCase()
{
    cutevariant->closeDatabase();
}

void Sample::testCreateSample()
{

    QVERIFY(cvar::SampleDataMapper::i()->insertOne({"sacha"}));
    QVERIFY(cvar::SampleDataMapper::i()->list().size() > 0);
    QCOMPARE(cvar::SampleDataMapper::i()->list().first().name(),"sacha");

}

void Sample::toUpper_data()
{
      QTest::addColumn<QString>("string");
      QTest::addColumn<QString>("result");

      QTest::newRow("all lower") << "hello" << "HELLO";
      QTest::newRow("mixed")     << "Hello" << "HELLO";
      QTest::newRow("all upper") << "HELLO" << "HELLO";
}

void Sample::toUpper()
{
       QFETCH(QString, string);
       QFETCH(QString, result);

       QCOMPARE(string.toUpper(), result);
}



QTEST_APPLESS_MAIN(Sample)

#include "tst_sample.moc"
