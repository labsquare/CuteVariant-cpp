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


    //    if (VariantReaderFactory::isGzip(mProgressDevice))
    //        reader.reset(VariantReaderFactory::createVariantReader(new KCompressionDevice(mProgressDevice,true, KCompressionDevice::GZip)));

    //    else
    reader.reset(VariantReaderFactory::createVariantReader(mProgressDevice));


    if (reader.isNull())
    {
        qCritical()<<Q_FUNC_INFO<<"cannot create reader";
        return false;
    }



    qInfo()<<"Start Importing "<<filename <<" with format "<<format;

    QElapsedTimer timer;
    timer.start();

    // writeProject(info.baseName());
    // writeBed();
    // writeFileInfo(filename);
    // writeMetadatas(reader.data());
    writeSamples(reader.data());
    writeFields(reader.data());
    // writeGenotypeFields(reader.data());
    writeVariants(reader.data());
    // writeGenotypeFields(reader.data());

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
    //    QSqlQuery query;
    //    qInfo()<<"Create Project"<<name;

    //    query.exec(QStringLiteral("DROP TABLE IF EXISTS `project`"));
    //    query.exec(QStringLiteral("CREATE TABLE project ("
    //                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //                              "name TEXT NOT NULL,"
    //                              "version TEXT,"
    //                              "creation_date TEXT,"
    //                              "build TEXT"
    //                              ")"));

    //    query.prepare(QStringLiteral("INSERT INTO project (name,version,creation_date) VALUES (:name, :version, :date)"));

    //    query.bindValue(0, name);
    //    query.bindValue(1,qApp->applicationVersion());
    //    query.bindValue(2, QDateTime::currentDateTime().toString(Qt::ISODate));

    //    if (!query.exec())
    //    {
    //        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
    //        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
    //    }
}

//-----------------------------------------------------------------------
void Importer::writeFileInfo(const QString &filename)
{
    //    QSqlQuery query;
    //    QFileInfo info(filename);
    //    query.exec(QStringLiteral("DROP TABLE IF EXISTS `file`"));
    //    query.exec(QStringLiteral("CREATE TABLE `file` ("
    //                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //                              "name TEXT NOT NULL,"
    //                              "size TEXT,"
    //                              "creation_date TEXT,"
    //                              "md5sum TEXT"
    //                              ")"));


    //    query.prepare(QStringLiteral("INSERT into `file` VALUES (NULL,?,?,?,? )"));

    //    query.bindValue(0, info.fileName());
    //    query.bindValue(1, info.size());
    //    query.bindValue(2, info.created().toString(Qt::ISODate));
    //   // query.bindValue(3, SqliteManager::md5sum(filename));


    //    if (!query.exec())
    //    {
    //        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
    //        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
    //    }
}
//-----------------------------------------------------------------------

void Importer::writeBed()
{
    //    QSqlQuery query;
    //    query.exec(QStringLiteral("DROP TABLE IF EXISTS `bedfiles`"));

    //    query.exec(QStringLiteral("CREATE TABLE `bedfiles` ("
    //                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //                              "filename TEXT NOT NULL,"
    //                              "table_name TEXT NOT NULL,"
    //                              "md5 TEXT NOT NULL,"
    //                              "count INTEGER DEFAULT 0"
    //                              ")"));

    //    // drop all regions if exists
    //    for (const QString& table : QSqlDatabase::database().tables())
    //    {
    //        if (table.startsWith("bed_"))
    //            query.exec(QStringLiteral("DROP TABLE IF EXISTS `%1`").arg(table));

    //    }
}

//-----------------------------------------------------------------------

void Importer::writeMetadatas(AbstractVariantReader *reader)
{
    //    qInfo() <<"Create meta datas";
    //    emit importProgressChanged(0,QString("Create metadatas"));

    //    QSqlQuery query;
    //    query.exec(QStringLiteral("DROP TABLE IF EXISTS `filemetas`"));
    //    query.exec(QStringLiteral("CREATE TABLE `filemetas` ("
    //                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    //                              "key TEXT NOT NULL,"
    //                              "value TEXT"
    //                              ")"));

    //    QHash<QString, QVariant> hash = reader->metadatas();

    //    emit importRangeChanged(0,hash.size());
    //    emit importProgressChanged(0,QString("Import file metadatas"));

    //    QSqlDatabase::database().transaction();

    //    int index = 0;
    //    for (auto it = hash.begin(); it != hash.end(); ++it, ++index)
    //    {
    //        query.prepare(QStringLiteral("INSERT into `filemetas` VALUES (NULL,?,?)"));
    //        query.bindValue(0, it.key());
    //        query.bindValue(1, it.value());

    //        emit importProgressChanged(index,QString("Import metadata %1").arg(it.key()));

    //        if (!query.exec())
    //        {
    //            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
    //            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
    //        }
    //    }

    //    QSqlDatabase::database().commit();
}
//-----------------------------------------------------------------------

void Importer::writeSamples(AbstractVariantReader *reader)
{
    qDebug()<<Q_FUNC_INFO<<"Import Samples";

    emit importProgressChanged(100, "import samples");
    SampleDataMapper::i()->createTable();
    SampleDataMapper::i()->insert(reader->samples());

}
//-----------------------------------------------------------------------

void Importer::writeFields(AbstractVariantReader *reader)
{
    qDebug()<<Q_FUNC_INFO<<"Import Fields";
    emit importProgressChanged(100, "import fields");
    FieldDataMapper::i()->createTable();
    FieldDataMapper::i()->insert(reader->fields());

}
//-----------------------------------------------------------------------


void Importer::writeVariants(AbstractVariantReader *reader)
{

    qDebug()<<Q_FUNC_INFO<<"Import variants";

    VariantDataMapper::i()->setDynamicFields(reader->fields());
    VariantDataMapper::i()->createTable();

    // Not sure it should be here ...
    reader->device()->open(QIODevice::ReadOnly);

    emit importRangeChanged(0, int(mFileSize));

    VariantDataMapper::i()->beginBulkInsert();

    while (!reader->device()->atEnd()){

        Variant v  = reader->readVariant();
        VariantDataMapper::i()->bulkInsert(v);
        //qDebug()<<v.chromosom()<<" "<<v.position();
        emit importProgressChanged(int(mProgressDevice->size()));

    }

    qDebug()<<"done";



    VariantDataMapper::i()->endBulkInsert();

    reader->device()->close();

}
//-----------------------------------------------------------------------

}
