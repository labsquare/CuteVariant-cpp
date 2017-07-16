#include <QApplication>
#include <QtCore>
#include "ui/mainwindow.h"



int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    app.setApplicationName("CuteVariant");
    app.setOrganizationName("Labsquare");
    app.setOrganizationDomain("labsquare.org");
    app.setApplicationVersion("0.0.1");



    MainWindow w;
    w.show();

    return app.exec();
}
