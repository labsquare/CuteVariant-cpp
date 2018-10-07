#include <QtTest>
#include <chrono>
#include <thread>
#include "cutevariant.h"
#include "importer.h"

class Import : public QObject
{
    Q_OBJECT


private slots:
    void import_vcf_gz();
    void import_vcf();
    void import_vcf2();

};



void Import::import_vcf()
{
    QVERIFY(QFile::exists(EXEMPLE_VCF_PATH));
    QFile::remove("/tmp/cutevariant.db");
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant.db"));
    cvar::Importer importer;
    importer.import(EXEMPLE_VCF_PATH);
    cutevariant->closeDatabase();
}

void Import::import_vcf2()
{
    QVERIFY(QFile::exists("/home/sacha/cvtest/test.vcf"));
    QFile::remove("/tmp/cutevariant.db");
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant.db"));
    cvar::Importer importer;
    importer.import("/home/sacha/cvtest/test.vcf");
    cutevariant->closeDatabase();
}

void Import::import_vcf_gz()
{

    QVERIFY(QFile::exists(EXEMPLE_VCF_GZ_PATH));
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant2.db"));
    cvar::Importer importer;
    importer.import(EXEMPLE_VCF_GZ_PATH);
    cutevariant->closeDatabase();

}



QTEST_APPLESS_MAIN(Import)

#include "tst_import.moc"
