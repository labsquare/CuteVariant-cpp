#include <QApplication>
#include <QtCore>
#include "project.h"

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    app.setApplicationName("CuteVariant");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("labsquare.org");
    app.setApplicationVersion("0.0.1");

    core::Project prj("/tmp/variant.db");

    prj.importFile("/tmp/TRIO1.family.vcf");



}
