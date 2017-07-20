#include <QApplication>
#include <QtCore>
#include "ui/mainwindow.h"
#include "project.h"
#include "genotype.h"

#include "querybuilder.h"

using namespace core;

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    app.setApplicationName("CuteVariant");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("labsquare.org");
    app.setApplicationVersion("0.0.1");


    MainWindow win;
    win.show();


    app.exec();





}
