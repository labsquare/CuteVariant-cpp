#include <QApplication>
#include <QtCore>
#include "field.h"

int main(int argc, char **argv)
{

    QApplication app(argc, argv);

    Field f("test","test");

    qDebug()<<f.name();


    return app.exec();
}
