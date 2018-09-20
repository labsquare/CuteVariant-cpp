#include <QtTest>
#include "cutevariant.h"
#include "importer.h"
#include "querybuilder.h"
#include "viewdatamapper.h"

class View : public QObject
{
    Q_OBJECT


private slots:
    void initTestCase();
    void cleanupTestCase();
    void createView();
    void intersection();

};

void View::initTestCase()
{
    QFile::remove("/tmp/cutevariant.db");
    QVERIFY(cutevariant->openDatabase("/tmp/cutevariant.db"));
    QVERIFY(QSqlDatabase::database().isOpen());

    cvar::Importer importer;
    QVERIFY(importer.import(EXEMPLE_VCF_PATH));
}

void View::cleanupTestCase()
{
    cutevariant->closeDatabase();

}

void View::createView()
{
    cvar::QueryBuilder builder;
    builder.setColumns({"chr","pos"});
    builder.setTable("variants");
    builder.setCondition("ref='T' AND alt='C'");

    cvar::View view = builder.createView("sacha", "this is a test");

    QVERIFY(cvar::ViewDataMapper::i()->createView(view));



}

void View::intersection()
{
    cvar::View a = cvar::ViewDataMapper::i()->list()[0];
    cvar::View b = cvar::ViewDataMapper::i()->list()[1];

    QCOMPARE(a.name(), "variants");
    QCOMPARE(b.name(), "sacha");

    cvar::View c = a - b;
    c.setName("interab");
    c.setDescription("test intersection");

    QVERIFY(cvar::ViewDataMapper::i()->createView(c));

    cvar::View d = a - c ;
    d.setName("interd");
    d.setDescription("test intersection");


    QVERIFY(cvar::ViewDataMapper::i()->createView(d));

}

QTEST_APPLESS_MAIN(View)

#include "tst_view.moc"
