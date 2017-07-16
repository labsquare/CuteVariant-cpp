#include "variantimporter.h"

namespace core{

VariantImporter::VariantImporter()
{

}
//-------------------------------------------------------------------------------
bool VariantImporter::importFile(const QString &filename)
{
    QScopedPointer<AbstractVariantReader> reader;

    if (!QFile::exists(filename))
    {
        qDebug()<<"file doesn't exists";
        return false;
    }

    QFileInfo info(filename);
    if (info.suffix().toLower() == "vcf")
        reader.reset(new VCFVariantReader(filename));

    else
    {
        qDebug()<<Q_FUNC_INFO<<info.suffix()<<" format is not supported";
        return false;
    }

    qDebug()<<"import "<<filename;

    createSample(reader.data());
    createFields(reader.data());
    createVariants(reader.data());


}
//-------------------------------------------------------------------------------
void VariantImporter::createSample(AbstractVariantReader *reader)
{

    qDebug()<<"import samples";
    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS samples");
    query.exec(QString("CREATE TABLE samples ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "name TEXT NOT NULL"
                       ")"));


    for (Sample s : reader->samples()){
        query.exec(QString("INSERT INTO samples (name) VALUES ('%1')").arg(s.name()));

    }

}
//-------------------------------------------------------------------------------
void VariantImporter::createFields(AbstractVariantReader *reader)
{

    qDebug()<<"import fields";
    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS fields");
    query.exec(QString("CREATE TABLE fields ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "name TEXT NOT NULL,"
                       "description TEXT,"
                       "type TEXT"
                       ")"));


    for (Field f : reader->fields())
    {
        query.exec(QString("INSERT INTO fields (name,description) VALUES ('%1', '%2')").arg(f.name()).arg(f.description()));
    }


}
//-------------------------------------------------------------------------------
void VariantImporter::createVariants(AbstractVariantReader *reader)
{

    qDebug()<<"import variants";
    QString fieldQuery;

    int fieldCount = reader->fields().count();

    for (int i=0; i<fieldCount; ++i)
        fieldQuery.append(QString("ANN_%1 TEXT,").arg(i));

    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS variants");
    query.exec(QString("CREATE TABLE variants ("
                       "bin INT,"
                       "chr TEXT NOT NULL,"
                       "pos INTEGER NOT NULL,"
                       "ref TEXT NOT NULL,"
                       "alt TEXT NOT NULL,"
                       "%1"
                       "PRIMARY KEY (chr,pos,ref,alt)"
                       ") WITHOUT ROWID").arg(fieldQuery));


    QSqlDatabase::database().transaction();

    if (reader->device()->open(QIODevice::ReadOnly))
    {
        while (!reader->device()->atEnd())
        {
            Variant v = reader->readVariant();

            query.exec(QString("INSERT INTO variants (bin,chr,pos,ref,alt) VALUES (%1,'%2',%3,'%4','%5')")
                       .arg(-1).arg(v.chromosom()).arg(v.position()).arg(QString(v.ref())).arg(QString(v.alt())));

            qDebug()<<query.lastQuery();
            qDebug()<<query.lastError().text();
        }
    }

    QSqlDatabase::database().commit();
    qDebug()<<"variant installed";
}

void VariantImporter::createShema()
{
    qDebug()<<"create shema";
}


}
