#include <QtTest>

#include "cutevariant.h"
#include "importer.h"

class TestImport : public QObject
{
    Q_OBJECT


private slots:
    void initTestCase();
    void cleanupTestCase();

    void testImport();

};



void TestImport::initTestCase()
{
    QVERIFY(QFile::exists(EXEMPLE_VCF_PATH));
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant.db"));

}

void TestImport::cleanupTestCase()
{

}

void TestImport::testImport()
{
    cvar::Importer importer;
    importer.import(EXEMPLE_VCF_PATH);
}



QTEST_APPLESS_MAIN(TestImport)

#include "tst_testimport.moc"
