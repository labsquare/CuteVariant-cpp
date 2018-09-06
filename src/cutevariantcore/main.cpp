#include <iostream>
#include <QDebug>
#include <typeinfo>
#include <functional>
#include <vector>
#include "sampledatamapper.h"

#include "datamapper.h"
#include "test.h"
using namespace std;


int main(int argc, char **argv)
{


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/test.db");
    if (db.open())
    {

        qDebug()<<cvar::SampleDataMapper::i()->list().count();

        cvar::Sample s = cvar::SampleDataMapper::i()->list().first();

        cvar::SampleDataMapper::i()->remove(s);

        qDebug()<<cvar::SampleDataMapper::i()->list().count();


    }
    

    return 0;

}
