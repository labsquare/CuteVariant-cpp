#include "mainwindow.h"
#include <QApplication>
#include "project.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Project prj("test.db");
    prj.createSchema();




    return a.exec();
}
