//#include <QApplication>
#include <QtCore>

#include "project.h"
#include "genotype.h"
#include "filterdialog.h"
#include "qfonticon.h"
#include "mainwindow.h"
using namespace cvar;

int main(int argc, char **argv)
{


    QApplication app(argc, argv);
    app.setApplicationName("CuteVariant");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("labsquare.org");
    app.setApplicationVersion("0.0.1");

    QFontIcon::addFont(":/Flaticon");

    //    Project prj("/tmp/variant.db");
    //    prj.importFile("/tmp/TRIO1.family.vcf");


    //    for (Field f : reader->parseHeader("INFO"))
    //    {
    //        qDebug()<<f.colname();
    //    }


    MainWindow win;
    win.show();









    app.exec();





}
