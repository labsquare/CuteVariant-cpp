#include <QtTest/QtTest>
#include <QtCore>
#include <iostream>
#include "vqlparser.h"
#include "variantquery.h"

using namespace cvar;

class TestVql: public QObject
{
    Q_OBJECT
private slots:


    void testTableName();
    void testColumns();
    void testCondition();
    void testRegion();
    void testSample();

    void testVariantQuery();



};

void TestVql::testTableName()
{
    VqlParser parser;

    parser.setQuery("SELECT chr FROM variants");
    QVERIFY(parser.tableName() == "variants");

    parser.setQuery("SELECT chr FROM variants WHERE chr==3");
    QVERIFY(parser.tableName() == "variants");

    parser.setQuery("SELECT chr FROM variants WHERE chr==4 AND a < 3 REGION truc");
    QVERIFY(parser.tableName() == "variants");

    parser.setQuery("SELECT chr FROM variants REGION truc");
    QVERIFY(parser.tableName() == "variants");
}

void TestVql::testColumns()
{
    VqlParser parser;

    parser.setQuery("SELECT chr FROM variants");
    QVERIFY(parser.columns().size() == 1);
    QVERIFY(parser.columns().first() == "chr");

    parser.setQuery("SELECT chr,pos,ref FROM variants");
    QVERIFY(parser.columns().size() == 3);
    QVERIFY(parser.columns().at(0) == "chr");
    QVERIFY(parser.columns().at(1) == "pos");
    QVERIFY(parser.columns().at(2) == "ref");

    parser.setQuery("SELECT chr   ,   pos   ,   ref FROM variants");
    QVERIFY(parser.columns().size() == 3);
    QVERIFY(parser.columns().at(0) == "chr");
    QVERIFY(parser.columns().at(1) == "pos");
    QVERIFY(parser.columns().at(2) == "ref");

    parser.setQuery(R"(SELECT chr, genotype("sacha").gt ,phenotype("sacha").sexe FROM variants WHERE a=3 AND sacha)");
    QVERIFY(parser.columns().size() == 3);
    QVERIFY(parser.columns().at(0) == "chr");
    QVERIFY(parser.columns().at(1) == R"(genotype("sacha").gt)");
    QVERIFY(parser.columns().at(2) == R"(phenotype("sacha").sexe)");


}

void TestVql::testCondition()
{
    VqlParser parser;

    parser.setQuery("SELECT chr FROM variants WHERE a=3");
    QVERIFY(parser.conditions() == "a=3");

    parser.setQuery("SELECT chr FROM variants WHERE a=3 AND chr>4");
    QVERIFY(parser.conditions() == "a=3 AND chr>4");

    parser.setQuery("SELECT chr FROM variants WHERE a=3 AND chr>4 REGION exonic");
    QVERIFY(parser.conditions() == "a=3 AND chr>4");

    parser.setQuery(R"(SELECT chr FROM variants WHERE genotype("sacha").gt =3 AND chr>4 REGION exonic)");
    QVERIFY(parser.conditions() == R"(genotype("sacha").gt =3 AND chr>4)");

    parser.setQuery(R"(SELECT chr FROM variants WHERE genotype("sacha").gt=3 AND (chr>4) OR ann.gene_name=name="GJB2"  REGION exonic)");
    QVERIFY(parser.conditions() == R"(genotype("sacha").gt=3 AND (chr>4) OR ann.gene_name=name="GJB2")");
}

void TestVql::testRegion()
{
    VqlParser parser;

    parser.setQuery("SELECT chr FROM variants WHERE a=3 REGION exonic");
    QVERIFY(parser.region() == "exonic");

    parser.setQuery("SELECT chr FROM variants REGION exonic");
    QVERIFY(parser.region() == "exonic");

}

void TestVql::testSample()
{
    VqlParser parser;

    parser.setQuery("SELECT chr, genotype(sacha).gt");
    QVERIFY(parser.samples().size() == 1);
    QVERIFY(parser.samples().first() == "sacha");

    parser.setQuery(R"(SELECT chr, genotype("sacha").gt)");
    QVERIFY(parser.samples().size() == 1);
    QVERIFY(parser.samples().first() == "sacha");


    parser.setQuery(R"(SELECT chr, genotype("sacha").gt FROM variants WHERE genotype("boby").gt = 1)");
    QVERIFY(parser.samples().size() == 2);
    QVERIFY(parser.samples().at(0) == "sacha");
    QVERIFY(parser.samples().at(1) == "boby");

}

void TestVql::testVariantQuery()
{
    VariantQuery query = VariantQuery::fromVql("SELECT chr FROM variants");
    QVERIFY(query.toSql() == "SELECT `variants`.id AS id,`variants`.`chr` as 'chr' FROM `variants` LIMIT 100 OFFSET 0");

}





QTEST_MAIN(TestVql)
#include "testvql.moc"