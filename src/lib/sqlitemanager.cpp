#include "sqlitemanager.h"

namespace core{

SqliteManager::SqliteManager()
{

}
//-------------------------------------------------------------------------------
bool SqliteManager::importFile(const QString &filename)
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

QList<Variant> SqliteManager::variants(const VariantQuery &query)
{
    QList<Variant> list;

    return list;
}

int SqliteManager::variantsCount(const VariantQuery &query)
{

    return 0;
}

bool SqliteManager::variantsTo(const VariantQuery &query, const QString &target)
{

    return false;
}
//-------------------------------------------------------------------------------
void SqliteManager::createProject(const QString &name)
{

    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS project");
    query.exec(QString("CREATE TABLE project ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "name TEXT NOT NULL,"
                       "version TEXT,"
                       "creation_date TEXT,"
                       "build TEXT"
                       ")"));

    query.exec(QString("INSERT INTO project (name,version,creation_date) VALUES ('%1','%2','%3')")
               .arg(name)
               .arg(qApp->applicationVersion())
               .arg(QDateTime::currentDateTime().toString(Qt::ISODate)));



}
//-------------------------------------------------------------------------------
void SqliteManager::createSample(AbstractVariantReader *reader)
{

    qDebug()<<"import samples";
    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS samples");
    query.exec(QString("CREATE TABLE samples ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "name TEXT NOT NULL"
                       ")"));


    QSqlDatabase::database().transaction();

    for (Sample s : reader->samples()){
        query.exec(QString("INSERT INTO samples (name) VALUES ('%1')").arg(s.name()));

    }
    QSqlDatabase::database().commit();

}
//-------------------------------------------------------------------------------
void SqliteManager::createFields(AbstractVariantReader *reader)
{

    qDebug()<<"import fields";
    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS fields");
    query.exec(QString("CREATE TABLE fields ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "colname TEXT NOT NULL,"
                       "name TEXT,"
                       "description TEXT,"
                       "type TEXT"
                       ")"));

    QSqlDatabase::database().transaction();

    for (Field f : reader->fields())
    {
        query.exec(QString("INSERT INTO fields (colname,name,description,type) VALUES ('%1', '%2','%3','%4')").arg(f.colname()).arg(f.name()).arg(f.description()).arg(f.typeName()));
    }
    QSqlDatabase::database().commit();


}
//-------------------------------------------------------------------------------
void SqliteManager::createVariants(AbstractVariantReader *reader)
{

    qDebug()<<"import variants";
    QString fieldQuery;

    QList<Field> fields =  reader->fields();

    for (Field f : fields){
        fieldQuery.append(QString("%1 %2,").arg(f.colname()).arg(f.sqliteType()));
    }

    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS variants");
    query.exec(QString("CREATE TABLE variants ("
                       "bin INT,"
                       "rs TEXT,"
                       "chr TEXT NOT NULL,"
                       "pos INTEGER NOT NULL,"
                       "ref TEXT NOT NULL,"
                       "alt TEXT NOT NULL,"
                       "qual REAL,"
                       "filter TEXT,"
                       "%1"
                       "PRIMARY KEY (chr,pos,ref,alt)"
                       ") WITHOUT ROWID").arg(fieldQuery));

    qDebug()<<query.lastQuery();
    qDebug()<<query.lastError().text();




    QSqlDatabase::database().transaction();

    if (reader->device()->open(QIODevice::ReadOnly))
    {
        while (!reader->device()->atEnd())
        {
            Variant v = reader->readVariant();

            QStringList annCols;
            QStringList annVals;

            for (Field f : fields){
                annCols.append(f.colname());
                annVals.append("'"+v.annotation(f.colname()).toString()+"'");
            }


            query.exec(QString("INSERT INTO variants (bin,rs,chr,pos,ref,alt,qual,filter,%9) VALUES (%1,'%2','%3',%4,'%5','%6',%7,'%8',%10)")
                       .arg(-1)
                       .arg(v.rsId())
                       .arg(v.chromosom())
                       .arg(v.position())
                       .arg(v.ref())
                       .arg(v.alt())
                       .arg(v.qual())
                       .arg(v.filter())
                       .arg(annCols.join(','))
                       .arg(annVals.join(','))
                       );

            qDebug()<<query.lastQuery();
            qDebug()<<query.lastError().text();
        }
    }

    QSqlDatabase::database().commit();
    qDebug()<<"variant installed";
}


}
