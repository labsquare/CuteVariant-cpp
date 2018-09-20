#include <QtTest>

#include "cutevariant.h"
#include "importer.h"

class Import : public QObject
{
    Q_OBJECT


private slots:
    void initTestCase();
    void cleanupTestCase();

    void testImport();

};



void Import::initTestCase()
{
    QVERIFY(QFile::exists(EXEMPLE_VCF_PATH));
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant.db"));

}

void Import::cleanupTestCase()
{
    cutevariant->closeDatabase();
}

void Import::testImport()
{
    cvar::Importer importer;
    importer.import(EXEMPLE_VCF_PATH);
}



QTEST_APPLESS_MAIN(Import)

#include "tst_import.moc"
