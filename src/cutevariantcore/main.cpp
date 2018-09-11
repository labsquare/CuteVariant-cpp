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

        //        QList<Field> fields = {
        //            {"chr", "variants","chromosom name", QVariant::String},
        //            {"pos", "variants","chromosom name", QVariant::DateTime},
        //            {"alt", "variants","chromosom name", QVariant::Int}
        //        };


        //        FieldDataMapper::i()->createTable();
        //        FieldDataMapper::i()->insert(fields);

        //        VariantDataMapper::i()->setDynamicFields(fields);
        //        VariantDataMapper::i()->createTable();





        QFile file("/tmp/test2.vcf");

        qDebug()<<"open";
        cvar::GenericVCFReader reader(&file);

        //            for (auto& s : reader.samples())
        //            {
        //                qDebug()<<s.name();
        //            }


        QList<Field> fields =  reader.fields();


        FieldDataMapper::i()->createTable();
        FieldDataMapper::i()->insert(fields);
        VariantDataMapper::i()->setDynamicFields(fields);
        VariantDataMapper::i()->createTable();

        SampleDataMapper::i()->createTable();
        SampleDataMapper::i()->insert(reader.samples());



        SampleDataMapper::i()->createTable();
        SampleDataMapper::i()->insert(reader.samples());

        file.open(QIODevice::ReadOnly);

        VariantDataMapper::i()->beginBulkInsert();

        while (!file.atEnd())
        {
            VariantDataMapper::i()->bulkInsert(reader.readVariant());
        }


        VariantDataMapper::i()->endBulkInsert();











    }
    

    return 0;

}
