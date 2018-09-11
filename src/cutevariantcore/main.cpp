#include <iostream>
#include <QDebug>
#include <typeinfo>
#include <functional>
#include <vector>
#include "sampledatamapper.h"
#include "fielddatamapper.h"
#include "regiondatamapper.h"
#include "variantdatamapper.h"
#include "viewdatamapper.h"
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





        QFile file("/home/sacha/test2.vcf");

        qDebug()<<"open";
        cvar::GenericVCFReader reader(&file);

        //            for (auto& s : reader.samples())
        //            {
        //                qDebug()<<s.name();
        //            }


        QList<Field> fields =  reader.fields();


        FieldDataMapper::i()->createTable();
        FieldDataMapper::i()->insert(fields);
//        VariantDataMapper::i()->setDynamicFields(fields);
//        VariantDataMapper::i()->createTable();

//        SampleDataMapper::i()->createTable();
//        SampleDataMapper::i()->insert(reader.samples());

//        ViewDataMapper::i()->createTable();


//        SampleDataMapper::i()->createTable();
//        SampleDataMapper::i()->insert(reader.samples());


//        RegionDataMapper::i()->createTable();
//        RegionDataMapper::i()->insertOne({"chr3", 10, 400});

//        file.open(QIODevice::ReadOnly);


//        VariantDataMapper::i()->beginBulkInsert();

//        while (!file.atEnd())
//        {
//            VariantDataMapper::i()->bulkInsert(reader.readVariant());
//        }


//        VariantDataMapper::i()->endBulkInsert();

        View v1("test", "desc", 0);
        v1.setSql("SELECT * FROM variants WHERE pos > 400");

        View v2("test", "desc", 0);
        v2.setSql("SELECT * FROM variants WHERE pos > 300");

        View v3 = v1 - (v1 & v2);

        qDebug()<<v3.sql();











    }
    

    return 0;

}
