#include <QtTest>

// add necessary includes here

class TestVariant : public QObject
{
    Q_OBJECT


private slots:
    void initTestCase();
    void cleanupTestCase();

};


void TestVariant::initTestCase()
{


}

void TestVariant::cleanupTestCase()
{

}


QTEST_APPLESS_MAIN(TestVariant)

#include "tst_testvariant.moc"
