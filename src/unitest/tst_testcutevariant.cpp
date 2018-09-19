#include <QtTest>
#include "cutevariant.h"
#include "importer.h"
#include "datamapper/sampledatamapper.h"

class TestCuteVariant : public QObject
{
    Q_OBJECT

public:
    void initTestCase();
    void cleanupTestCase();

    const QString vcf = QStringLiteral(EXEMPLE_PATH) +"snpeff.example.vcf" ;

private slots:


};


void TestCuteVariant::initTestCase()
{
    QVERIFY2(cutevariant->openDatabase("/tmp/cutevariant.db"),"open database");

    cvar::Importer importer;
    QVERIFY(importer.import(vcf));

}

void TestCuteVariant::cleanupTestCase()
{

}



QTEST_APPLESS_MAIN(TestCuteVariant)

#include "tst_testcutevariant.moc"
