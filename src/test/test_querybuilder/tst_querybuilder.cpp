#include <QtTest>
#include <QSqlQuery>
#include "querybuilder.h"
#include "cutevariant.h"
#include "importer.h"

class QueryBuilder : public QObject
{
    Q_OBJECT


private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_Query();
    void test_createView();



};


void QueryBuilder::initTestCase()
{
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant.db"));
    QVERIFY(QSqlDatabase::database().isOpen());

    cvar::Importer importer;
    QVERIFY(importer.import(EXEMPLE_VCF_PATH));
}

void QueryBuilder::cleanupTestCase()
{
    cutevariant->closeDatabase();
}

void QueryBuilder::test_Query()
{
    QSqlQuery q;
    cvar::QueryBuilder builder;
    builder.setColumns({"chr","pos"});
    builder.setTable("variants");
    QCOMPARE(builder.toSql(), "SELECT `chr`,`pos` FROM `variants`");
    QVERIFY(q.exec(builder.toSql()));

    builder.setCondition("ref='T' AND alt='C'");
    QCOMPARE(builder.toSql(), "SELECT `chr`,`pos` FROM `variants` WHERE ref='T' AND alt='C'");
    QVERIFY(q.exec(builder.toSql()));


    builder.addSortColumns("pos", Qt::DescendingOrder);

    QCOMPARE(builder.toSql(), "SELECT `chr`,`pos` FROM `variants` WHERE ref='T' AND alt='C' ORDER BY `pos` DESC");
    QVERIFY(q.exec(builder.toSql()));

    builder.setGroupBy("chr");
    QCOMPARE(builder.toSql(), "SELECT `chr`,`pos` FROM `variants` WHERE ref='T' AND alt='C' GROUP BY `chr` ORDER BY `pos` DESC");
    QVERIFY(q.exec(builder.toSql()));


}

void QueryBuilder::test_createView()
{
    cvar::QueryBuilder builder;
    builder.setColumns({"sacha","boby"});
    builder.setTable("variants");
    builder.setCondition("age=43 AND sexe=1");
    builder.setGroupBy("sacha");
    builder.addSortColumns("sacha", Qt::DescendingOrder);

    cvar::View view = builder.createView("sacha", "this is a test");

    QCOMPARE(view.sql(), "SELECT rowid, * FROM `variants` WHERE age=43 AND sexe=1");



}

QTEST_APPLESS_MAIN(QueryBuilder)

#include "tst_querybuilder.moc"
