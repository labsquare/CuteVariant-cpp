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
        qWarning()<<Q_FUNC_INFO<<info.suffix()<<" format is not supported";
        return false;
    }

    // Start import
    qInfo()<<"Start Importing "<<filename <<"";

    QElapsedTimer timer;
    timer.start();

    createSample(reader.data());
    createFields(reader.data());
    createVariants(reader.data());
    createGenotypes(reader.data());

    qInfo()<< "Import done in " << timer.elapsed() << "milliseconds";

    return true;
}

//-------------------------------------------------------------------------------
QList<Sample> SqliteManager::samples() const
{
    QList<Sample> samples;
    QSqlQuery query(QStringLiteral("SELECT * FROM `samples`"));
    while(query.next())
    {
        Sample sample;
        sample.setId(query.value("id").toInt());
        sample.setName(query.value("name").toString());
        samples.append(sample);
    }

    return samples;
}
//-------------------------------------------------------------------------------
QList<Field> SqliteManager::fields() const
{
    QList<Field> fields;
    QSqlQuery query(QStringLiteral("SELECT * FROM `fields`"));
    while(query.next())
    {
        Field field;
        field.setId(query.value("id").toInt());
        field.setColname(query.value("colname").toString());
        field.setName(query.value("name").toString());
        field.setDescription(query.value("description").toString());
        field.setType(query.value("type").toString());
        fields.append(field);
    }
    return fields;
}

QList<Field> SqliteManager::genotype(const Sample &sample)
{
//    QList<Field> fields;
//    QSqlQuery query(QStringLiteral("SELECT * FROM `genotypes` WHERE sample_id = %1").arg(sample.id()));
//    while(query.next())
//    {

//        Field field;
//        //field.setId(query.value("id").toInt());
//        //field.setColname(query.value("colname").toString());
//        field.setName(query.value("name").toString());
//        field.setDescription(query.value("description").toString());
//        field.setType(query.value("type").toString());
//        fields.append(field);
//    }
//    return fields;


}
//-------------------------------------------------------------------------------
QString SqliteManager::buildVariantQuery(const QString &raw)
{
    mQueryBuilder.fromRawQuery(raw);

    QHash<QString, int> sids;
    for (Sample s : samples())
        sids[s.name()] = s.id();

        mQueryBuilder.setSampleIds(sids);



    return mQueryBuilder.toSql();
}
//-------------------------------------------------------------------------------
void SqliteManager::createProject(const QString &name)
{
    QSqlQuery query;
    qInfo()<<"Create Project"<<name;

    query.exec(QStringLiteral("DROP TABLE IF EXISTS `project`"));
    query.exec(QStringLiteral("CREATE TABLE project ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name TEXT NOT NULL,"
                              "version TEXT,"
                              "creation_date TEXT,"
                              "build TEXT"
                              ")"));

    query.prepare(QStringLiteral("INSERT INTO project (name,version,creation_date) VALUES (:name, :version, :date)"));

    query.bindValue(0, name);
    query.bindValue(1,qApp->applicationVersion());
    query.bindValue(2, QDateTime::currentDateTime().toString(Qt::ISODate));

    if (!query.exec())
    {
        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
    }

}
//-------------------------------------------------------------------------------
void SqliteManager::createSample(AbstractVariantReader *reader)
{
    QSqlQuery query;
    mSamplesIds.clear();
    qInfo()<<"Import Samples";

    query.exec(QStringLiteral("DROP TABLE IF EXISTS samples"));
    query.exec(QStringLiteral("CREATE TABLE samples ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name TEXT NOT NULL"
                              ")"));
    query.exec(QStringLiteral("CREATE INDEX samples_idx ON samples (id)"));

    QSqlDatabase::database().transaction();

    for (Sample s : reader->samples()){
        query.prepare(QStringLiteral("INSERT INTO samples (name) VALUES (:name)"));
        query.bindValue(0, s.name());

        if (!query.exec())
        {
            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
        }

        // store samples ids for later
        else
            mSamplesIds[s.name()] = query.lastInsertId().toInt();

    }

    QSqlDatabase::database().commit();

}
//-------------------------------------------------------------------------------
void SqliteManager::createFields(AbstractVariantReader *reader)
{

    qDebug()<<"Import Fields";
    QSqlQuery query;

    query.exec(QStringLiteral("DROP TABLE IF EXISTS fields"));
    query.exec(QStringLiteral("CREATE TABLE fields ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "colname TEXT NOT NULL,"
                              "name TEXT,"
                              "description TEXT,"
                              "type TEXT"
                              ")"));

    QSqlDatabase::database().transaction();
    for (Field f : reader->fields())
    {
        query.prepare(QStringLiteral("INSERT INTO fields (colname,name,description,type) VALUES (?,?,?,?)"));
        query.addBindValue(f.colname());
        query.addBindValue(f.name());
        query.addBindValue(f.description());
        query.addBindValue(f.typeName());
        //qInfo()<<"Create "<<f.name();

        if (!query.exec())
        {
            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
        }

    }
    QSqlDatabase::database().commit();

}
//-------------------------------------------------------------------------------
void SqliteManager::createVariants(AbstractVariantReader *reader)
{

    qDebug()<<"Import Variants";

    // First : Get Fields saved previously to construct the table
    QList<Field> fields =  reader->fields();
    QStringList fieldColumns;

    for (Field f : fields){
        fieldColumns.append(QStringLiteral("%1 %2").arg(f.colname()).arg(f.sqliteType()));
    }

    // Second : Create the variant table
    QSqlQuery query;

    query.exec(QStringLiteral("DROP TABLE IF EXISTS variants"));
    query.exec(QStringLiteral("CREATE TABLE variants ("
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
                              ")").arg(fieldColumns.join(',')));

    if (query.lastError().isValid())
    {
        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
    }

    query.exec(QStringLiteral("CREATE INDEX variants_idx ON variants (chr,pos,ref,alt);"));
    query.exec(QStringLiteral("CREATE INDEX variants_idx2 ON variants (id);"));

    // Third : Parse all file and get Variant

    QSqlDatabase::database().transaction();

    if (reader->open())
    {
        while (!reader->atEnd())
        {
            Variant v = reader->readVariant();
            QString placeHolders = QString(",?").repeated(fields.size() + 8);

            query.prepare(QStringLiteral("INSERT INTO variants VALUES (NULL%1)").arg(placeHolders));
            query.addBindValue("-1");
            query.addBindValue(v.rsId());
            query.addBindValue(v.chromosom());
            query.addBindValue(v.position());
            query.addBindValue(v.ref());
            query.addBindValue(v.alt());
            query.addBindValue(v.qual());
            query.addBindValue(v.filter());

            for (Field f : fields)
                query.addBindValue(v[f.colname()]);


            if (!query.exec())
            {
                qWarning()<<Q_FUNC_INFO<<query.lastQuery();
                qWarning()<<Q_FUNC_INFO<<query.lastError().text();
            }

            // store variant ids
            else
                mVariantIds[v.name()].append(query.lastInsertId().toInt());
        }
    }

    QSqlDatabase::database().commit();
    reader->close();
}

void SqliteManager::createGenotypes(AbstractVariantReader *reader)
{
    qDebug()<<"Import Genotypes";

    // First : get genotype fields saved previously to construct the table
    QList<Field> fields = reader->genotypeFields();
    QStringList colnames;
    for (Field f : fields){
        colnames.append(QString("%1 %2").arg(f.name()).arg(f.sqliteType()));
    }

    // GT Fields is mandatory. If it doesn't exists add a new one
    if (!colnames.contains("GT TEXT"))
    {
        qWarning()<<"The file doesn't contains  GT genotype data";
        colnames.append("GT TEXT");
    }


    // Second : Create Table

    QSqlQuery query;
    query.exec(QStringLiteral("DROP TABLE IF EXISTS genotypes"));
    query.exec(QStringLiteral("CREATE TABLE genotypes ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "sample_id INTEGER NOT NULL,"
                              "variant_id INTEGER NOT NULL,"
                              "%1"
                              ")").arg(colnames.join(",")));

    query.exec(QStringLiteral("CREATE INDEX genotypes_idx ON genotypes (variant_id, sample_id);"));

    // Thrid : Import genotype

    QSqlDatabase::database().transaction();
    if (reader->open())
    {
        while (!reader->atEnd())
        {
            Genotype geno = reader->readGenotype();


            int sample_id = mSamplesIds[geno.sample().name()];
            for (quint64 variant_id : mVariantIds[geno.variant().name()])
            {
                QString placeHolders = QString(",?").repeated(fields.size() + 2);
                query.prepare(QStringLiteral("INSERT INTO genotypes VALUES (NULL%1)").arg(placeHolders));
                query.addBindValue(sample_id);
                query.addBindValue(variant_id);

                for (Field f : fields)
                    query.addBindValue(geno.annotation(f.name()));

                if (!query.exec())
                {
                    qWarning()<<Q_FUNC_INFO<<query.lastQuery();
                    qWarning()<<Q_FUNC_INFO<<query.lastError().text();
                }
            }
        }

    }
    reader->close();
    QSqlDatabase::database().commit();
}


}
