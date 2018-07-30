#include "importer.h"
namespace cvar {
Importer::Importer(QObject *parent) : QObject(parent)
{

}

bool Importer::import(const QString &filename, VariantReaderFactory::Format format)
{
    // test if file exists
    if (!QFile::exists(filename))
    {
        qDebug()<<"file doesn't exists";
        return false;
    }



    // Actual file support .. Will change in the future .
    QFileInfo info(filename);
    mFileSize = info.size();


    // if gzip file : progressFile is the uncompress file to keep reading tracking
    // if not : progressFile is the file
    mProgressDevice = new QFile(filename);
    QScopedPointer<AbstractVariantReader> reader;


    if (VariantReaderFactory::isGzip(mProgressDevice))
        reader.reset(VariantReaderFactory::createVariantReader(new KCompressionDevice(mProgressDevice,true, KCompressionDevice::GZip)));

    else
        reader.reset(VariantReaderFactory::createVariantReader(mProgressDevice));


    if (reader.isNull())
    {
        qCritical()<<Q_FUNC_INFO<<"cannot create reader";
        return false;
    }



    qInfo()<<"Start Importing "<<filename <<" with format "<<format;

    QElapsedTimer timer;
    timer.start();

    writeProject(info.baseName());
    writeBed();
    writeFileInfo(filename);
    writeMetadatas(reader.data());
    writeSamples(reader.data());
    writeFields(reader.data());
    writeGenotypeFields(reader.data());
    writeVariants(reader.data());
    writeGenotypeFields(reader.data());

    qInfo()<< "Import done in " << timer.elapsed() << "milliseconds";

    emit importRangeChanged(0,1);
    emit importProgressChanged(1,QString("Done in %1 ms").arg(timer.elapsed()));

    return true;
}
//-----------------------------------------------------------------------
QFuture<bool> Importer::asyncImport(const QString &filename, VariantReaderFactory::Format format)
{
    return QtConcurrent::run(this, &Importer::import, filename, format);

}
//-----------------------------------------------------------------------
void Importer::writeProject(const QString &name)
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

//-----------------------------------------------------------------------
void Importer::writeFileInfo(const QString &filename)
{
    QSqlQuery query;
    QFileInfo info(filename);
    query.exec(QStringLiteral("DROP TABLE IF EXISTS `file`"));
    query.exec(QStringLiteral("CREATE TABLE `file` ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name TEXT NOT NULL,"
                              "size TEXT,"
                              "creation_date TEXT,"
                              "md5sum TEXT"
                              ")"));


    query.prepare(QStringLiteral("INSERT into `file` VALUES (NULL,?,?,?,? )"));

    query.bindValue(0, info.fileName());
    query.bindValue(1, info.size());
    query.bindValue(2, info.created().toString(Qt::ISODate));
   // query.bindValue(3, SqliteManager::md5sum(filename));


    if (!query.exec())
    {
        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
    }
}
//-----------------------------------------------------------------------

void Importer::writeBed()
{
    QSqlQuery query;
    query.exec(QStringLiteral("DROP TABLE IF EXISTS `bedfiles`"));

    query.exec(QStringLiteral("CREATE TABLE `bedfiles` ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "filename TEXT NOT NULL,"
                              "table_name TEXT NOT NULL,"
                              "md5 TEXT NOT NULL,"
                              "count INTEGER DEFAULT 0"
                              ")"));

    // drop all regions if exists
    for (const QString& table : QSqlDatabase::database().tables())
    {
        if (table.startsWith("bed_"))
            query.exec(QStringLiteral("DROP TABLE IF EXISTS `%1`").arg(table));

    }
}
//-----------------------------------------------------------------------

void Importer::writeMetadatas(AbstractVariantReader *reader)
{
    qInfo() <<"Create meta datas";
    emit importProgressChanged(0,QString("Create metadatas"));

    QSqlQuery query;
    query.exec(QStringLiteral("DROP TABLE IF EXISTS `filemetas`"));
    query.exec(QStringLiteral("CREATE TABLE `filemetas` ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "key TEXT NOT NULL,"
                              "value TEXT"
                              ")"));

    QHash<QString, QVariant> hash = reader->metadatas();

    emit importRangeChanged(0,hash.size());
    emit importProgressChanged(0,QString("Import file metadatas"));

    QSqlDatabase::database().transaction();

    int index = 0;
    for (auto it = hash.begin(); it != hash.end(); ++it, ++index)
    {
        query.prepare(QStringLiteral("INSERT into `filemetas` VALUES (NULL,?,?)"));
        query.bindValue(0, it.key());
        query.bindValue(1, it.value());

        emit importProgressChanged(index,QString("Import metadata %1").arg(it.key()));

        if (!query.exec())
        {
            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
        }
    }

    QSqlDatabase::database().commit();
}
//-----------------------------------------------------------------------

void Importer::writeSamples(AbstractVariantReader *reader)
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

    QList<Sample> samples = reader->samples();
    emit importRangeChanged(0,samples.length());
    emit importProgressChanged(0,QString("Import samples"));

    for (int i=0; i< samples.length(); ++i){
        emit importProgressChanged(i, QString("%1 imported").arg(samples[i].name()));
        query.prepare(QStringLiteral("INSERT INTO samples (name) VALUES (:name)"));
        query.bindValue(0, samples[i].name());

        if (!query.exec())
        {
            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
        }

        // store samples ids for later
        else
            mSamplesIds[samples[i].name()] = query.lastInsertId().toInt();

    }

    QSqlDatabase::database().commit();
}
//-----------------------------------------------------------------------

void Importer::writeFields(AbstractVariantReader *reader)
{
    qDebug()<<"Import Fields";

    QSqlQuery query;

    query.exec(QStringLiteral("DROP TABLE IF EXISTS fields"));
    query.exec(QStringLiteral("CREATE TABLE fields ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "colname TEXT NOT NULL,"
                              "name TEXT,"
                              "description TEXT,"
                              "category TEXT,"
                              "type TEXT"
                              ")"));

    QSqlDatabase::database().transaction();

    // import default fields
    qDebug()<<"import default";
    query.exec(QStringLiteral("INSERT INTO fields (colname,name,description,category,type) VALUES ('chr','chr','Chromosome name','VARIANTS','TEXT') "));
    query.exec(QStringLiteral("INSERT INTO fields (colname,name,description,category,type) VALUES ('pos','pos','Position 1-based','VARIANTS','INTEGER')"));
    query.exec(QStringLiteral("INSERT INTO fields (colname,name,description,category,type) VALUES ('ref','ref','Reference allele','VARIANTS','TEXT') "));
    query.exec(QStringLiteral("INSERT INTO fields (colname,name,description,category,type) VALUES ('alt','alt','Alternative allele','VARIANTS','TEXT')"));
    query.exec(QStringLiteral("INSERT INTO fields (colname,name,description,category,type) VALUES ('qual','qual','Quality Phred','VARIANTS','REAL')"));
    query.exec(QStringLiteral("INSERT INTO fields (colname,name,description,category,type) VALUES ('filter','filter','Filter','VARIANTS','TEXT')"));

    qDebug()<<query.lastError().text();

    QList<Field> fields = reader->fields();
    emit importRangeChanged(0,fields.count());
    emit importProgressChanged(0,QString("Import Fields"));

    for (int i=0; i< fields.length(); ++i)
    {
        emit importProgressChanged(i,QString());

        query.prepare(QStringLiteral("INSERT INTO fields (colname,name,description,category,type) VALUES (?,?,?,?,?)"));
        query.addBindValue(fields[i].colname());
        query.addBindValue(fields[i].name());
        query.addBindValue(fields[i].description());
        query.addBindValue(fields[i].category());
        query.addBindValue(fields[i].typeName());

        if (!query.exec())
        {
            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
        }

    }

    QSqlDatabase::database().commit();
}
//-----------------------------------------------------------------------

void Importer::writeGenotypeFields(AbstractVariantReader *reader)
{
    qDebug()<<"Import genotype fields";

    QSqlQuery query;

    query.exec(QStringLiteral("DROP TABLE IF EXISTS genotype_fields"));
    query.exec(QStringLiteral("CREATE TABLE genotype_fields ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "colname TEXT NOT NULL,"
                              "name TEXT,"
                              "description TEXT,"
                              "category TEXT,"
                              "type TEXT"
                              ")"));

    QSqlDatabase::database().transaction();

    QList<Field> fields = reader->genotypeFields();
    emit importRangeChanged(0,fields.count());
    emit importProgressChanged(0,QString("Import Genotype fields"));

    for (int i=0; i<fields.size(); ++i)
    {
        emit importProgressChanged(i,QString());

        query.prepare(QStringLiteral("INSERT INTO genotype_fields (colname,name,description,category,type) VALUES (?,?,?,?,?)"));
        query.addBindValue(fields[i].colname());
        query.addBindValue(fields[i].name());
        query.addBindValue(fields[i].description());
        query.addBindValue(fields[i].category());
        query.addBindValue(fields[i].typeName());
        //qInfo()<<"Create "<<f.name();

        if (!query.exec())
        {
            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
        }

    }
    QSqlDatabase::database().commit();
}
//-----------------------------------------------------------------------

void Importer::writeVariants(AbstractVariantReader *reader)
{
    qDebug()<<"Import Variants";

    // First : Get Fields saved previously to construct the table
    QList<Field> fields =  reader->fields();
    QStringList fieldColumns;

    for (Field f : fields){
        fieldColumns.append(QStringLiteral("`%1` %2").arg(f.colname()).arg(f.sqliteType()));
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
        qWarning()<<Q_FUNC_INFO<<"cannot create variant table";
        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
    }

    query.exec(QStringLiteral("CREATE INDEX variants_idx ON variants (chr,pos,ref,alt);"));
    query.exec(QStringLiteral("CREATE INDEX variants_idx2 ON variants (id);"));
    query.exec(QStringLiteral("CREATE INDEX variants_idx3 ON variants (bin);"));


    // Third : Parse all file and get Variant

    QSqlDatabase::database().transaction();

    if (reader->open())
    {
        emit importRangeChanged(0, mFileSize);
        emit importProgressChanged(0,QString("Import Variants"));

        while (!reader->atEnd())
        {
            Variant v = reader->readVariant();
            if (v.isNull())
                continue;


            QString placeHolders = QString(",?").repeated(fields.size() + 8);

            if (reader->device()->pos() % 100 == 0)
                emit importProgressChanged(mProgressDevice->pos(),QString());

            query.prepare(QStringLiteral("INSERT INTO variants VALUES (NULL%1)").arg(placeHolders));
            query.addBindValue(v.bin());
            query.addBindValue(v.rsId());
            query.addBindValue(v.chromosom());
            query.addBindValue(v.position());
            query.addBindValue(v.ref());
            query.addBindValue(v.alt());
            query.addBindValue(v.qual());
            query.addBindValue(v.filter());

            for (Field f : fields)
                query.addBindValue(v[f.name()]);


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
//-----------------------------------------------------------------------

void Importer::writeGenotype(AbstractVariantReader *reader)
{
    qDebug()<<"Import Genotypes";

    if (mSamplesIds.keys().isEmpty())
    {
        qDebug()<<"No samples, No genotype to import";
        return;
    }

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
        emit importRangeChanged(0, mProgressDevice->size());
        emit importProgressChanged(0,QString("Import Genotype"));

        while (!reader->atEnd())
        {
            Genotype geno = reader->readGenotype();

            if (geno.isNull())
                continue;

            if (reader->device()->pos() % 100 == 0)
                emit importProgressChanged(mProgressDevice->pos(),QString());


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
