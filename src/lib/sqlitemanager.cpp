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

    QElapsedTimer timer;
    timer.start();

    qDebug()<<"import "<<filename;

    createSample(reader.data());
    createFields(reader.data());
    createVariants(reader.data());
    createGenotypes(reader.data());

    qDebug() << "Import done in " << timer.elapsed() << "milliseconds";



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

QList<Sample> SqliteManager::samples() const
{
    QSqlQuery query("SELECT * FROM samples");
    QList<Sample> samples;


    while(query.next())
    {
        Sample sample;
        sample.setId(query.value("id").toInt());
        sample.setName(query.value("name").toString());
        samples.append(sample);
    }

    return samples;

}

QStringList SqliteManager::samplesNames() const
{
    QStringList names;
    for (Sample s : samples())
        names.append(s.name());

    return names;

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
    mSamplesIds.clear();
    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS samples");
    query.exec(QString("CREATE TABLE samples ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "name TEXT NOT NULL"
                       ")"));


    QSqlDatabase::database().transaction();

    for (Sample s : reader->samples()){
        query.exec(QString("INSERT INTO samples (name) VALUES ('%1')").arg(s.name()));
        mSamplesIds.insert(s.name(), query.lastInsertId().toInt());

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
    QStringList fieldQuery;

    QList<Field> fields =  reader->fields();

    for (Field f : fields){
        fieldQuery.append(QString("%1 %2").arg(f.colname()).arg(f.sqliteType()));
    }

    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS variants");
    query.exec(QString("CREATE TABLE variants ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT ,"
                       "bin INT,"


                       "rs TEXT,"
                       "chr TEXT NOT NULL,"
                       "pos INTEGER NOT NULL,"
                       "ref TEXT NOT NULL,"
                       "alt TEXT NOT NULL,"
                       "qual REAL,"
                       "filter TEXT,"
                       "%1"
                       ")").arg(fieldQuery.join(',')));

    //    qDebug()<<query.lastQuery();
    //    qDebug()<<query.lastError().text();

    query.exec("CREATE INDEX variants_idx ON variants (chr,pos,ref,alt);");

    QSqlDatabase::database().transaction();

    if (reader->open())
    {
        while (!reader->atEnd())
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

            // store variant ids
            mVariantIds[v.name()].append(query.lastInsertId().toInt());

        }
    }

    QSqlDatabase::database().commit();
    reader->close();
}

void SqliteManager::createGenotypes(AbstractVariantReader *reader)
{
    qDebug()<<"import genotypes";
    QSqlQuery query;
    QStringList colnames;

    // create columns sql query

    QList<Field> fields = reader->genotypeFields();

    for (Field f : fields){
        colnames.append(QString("%1 %2").arg(f.name()).arg(f.sqliteType()));
    }

    if (!colnames.contains("GT TEXT"))
    {
        qCritical()<<"WARNING, THE FILE DOESN'T CONTAINS GT FIELD!!";
        colnames.append("GT TEXT");
    }


    query.exec("DROP TABLE IF EXISTS genotypes");
    query.exec(QString("CREATE TABLE genotypes ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "sample_id INTEGER NOT NULL,"
                       "variant_id INTEGER NOT NULL,"
                       "%1"
                       ")").arg(colnames.join(",")));

    QSqlDatabase::database().transaction();

    if (reader->open())
    {
        while (!reader->atEnd())
        {
            Genotype geno = reader->readGenotype();

            QStringList annoCols;
            QStringList annoVals;

            for (Field f : fields){

                annoCols.append(f.name());
                annoVals.append("'"+geno.annotation(f.name()).toString()+"'");
            }


            int sample_id  = mSamplesIds[geno.sample().name()];
            for (quint64 variant_id : mVariantIds[geno.variant().name()])
            {

                query.exec(QString("INSERT INTO genotypes (sample_id,variant_id,GT,%4) VALUES (%1,%2,'%3',%5)")
                           .arg(sample_id)
                           .arg(variant_id)
                           .arg(geno.rawGenotype())
                           .arg(annoCols.join(','))
                           .arg(annoVals.join(',').simplified())
                           );

            }
        }

    }
    reader->close();

    QSqlDatabase::database().commit();


}


}
