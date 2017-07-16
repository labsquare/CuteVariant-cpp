#include <QApplication>
#include <QtCore>
#include "project.h"

using namespace core;

int main(int argc, char **argv)
{

    QApplication app(argc, argv);

    QFile::remove("/tmp/cutevariant.db");

    Project prj("/tmp/cutevariant.db");

    prj.importFile("/tmp/exemples/freebayes.vcf");


    return app.exec();
}
