#include <iostream>
#include <QDebug>
#include <typeinfo>
#include <functional>
#include <vector>
#include "sampledatamapper.h"
#include "fielddatamapper.h"
#include "regiondatamapper.h"
#include "variantdatamapper.h"
#include "datamapper.h"
#include "test.h"

#include "genericvcfreader.h"

using namespace std;
using namespace cvar;

int main(int argc, char **argv)
{


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/test.db");
    if (db.open())
    {

        QList<Field> fields = {
            {"chr", "variants","chromosom name", QVariant::String},
            {"pos", "variants","chromosom name", QVariant::DateTime},
            {"alt", "variants","chromosom name", QVariant::Int}
        };


        FieldDataMapper::i()->createTable();
        FieldDataMapper::i()->insert(fields);

        VariantDataMapper::i()->setDynamicFields(fields);
        VariantDataMapper::i()->createTable();





        QFile file("/home/sacha/TRIO1.family.vcf");
        if (file.open(QIODevice::ReadOnly))
        {
            qDebug()<<"open";
            cvar::GenericVCFReader reader(&file);

//            for (auto& s : reader.samples())
//            {
//                qDebug()<<s.name();
//            }


            for (auto& f : reader.fields())
            {
                qDebug()<<f.name();
            }


        }








    }
    

    return 0;

}
