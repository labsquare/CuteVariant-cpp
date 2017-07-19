#include <QApplication>
#include <QtCore>
#include "project.h"
#include "genotype.h"

#include "variantquery.h"

using namespace core;

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    app.setApplicationName("CuteVariant");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("labsquare.org");
    app.setApplicationVersion("0.0.1");

    core::Project prj("/tmp/variant.db");
    prj.importFile("/tmp/TRIO1.family.vcf");



  //  VariantQuery q = VariantQuery::fromString("SELECT variant (AF>3 and AF<4) chr pos ref alt DP AO");

   // qDebug()<<q.toSql();



}
