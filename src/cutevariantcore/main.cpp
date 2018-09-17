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
#include "importer.h"

#include "test.h"

#include "genericvcfreader.h"
#include "variantreaderfactory.h"

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





        QFile file("/home/sacha/test3.vcf.gz");



        Importer * imp = new Importer;


        imp->import("/home/sacha/test3.vcf");


        //            for (auto& s : reader.samples())
        //            {
        //                qDebug()<<s.name();
        //            }


        //        QList<Field> fields =  reader.fields();


        //        FieldDataMapper::i()->createTable();
        //        FieldDataMapper::i()->insert(fields);
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













    }
    

    return 0;

}
