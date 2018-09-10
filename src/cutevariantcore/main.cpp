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

        QList<cvar::Sample> test = {{"sacha"}, {"perrine"}, {"julie"}};


        cvar::SampleDataMapper::i()->createTable();
        cvar::SampleDataMapper::i()->insert(test);

        for (auto & s : cvar::SampleDataMapper::i()->list())
        {
            qDebug()<<s.name();
        }




    }
    

    return 0;

}
