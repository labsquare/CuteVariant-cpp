#include <QtCore>
#include <QtWidgets>
#include "sample.h"


int main(int argc, char **argv)
{

    QApplication app(argc, argv);


    cvar::Sample * test = new cvar::Sample();


    qDebug()<<test->tableName();

    return app.exec();
}
