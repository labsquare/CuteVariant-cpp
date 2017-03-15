#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include "project.h"
#include "variantmodel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase::addDatabase("QSQLITE");

    MainWindow window;
    window.show();


    return a.exec();
}
