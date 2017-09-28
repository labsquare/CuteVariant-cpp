#include "sqlitemanager.h"
#include <quagzipfile.h>
namespace cvar{

SqliteManager::SqliteManager(QObject * parent)
    :QObject(parent)
{

}
//-------------------------------------------------------------------------------
SqliteManager::~SqliteManager()
{
}
//-------------------------------------------------------------------------------
bool SqliteManager::importFile(const QString &filename)
{
    qDebug()<<"SERIEUX ??";
  qDebug()<<"MODIF";
    if (!QFile::exists(filename))
    {
        qDebug()<<"file doesn't exists";
        return false;
    }

    QStringList suffixes = {"vcf","gz"};
    QFileInfo info(filename);

    if (!suffixes.contains(info.suffix().toLower()))
    {
        qDebug()<<"file suffix not suported";
        return false;
    }
    mProgressDevice =nullptr;
    QScopedPointer<AbstractVariantReader> reader;

    if (info.suffix().toLower() == "vcf"){
        mProgressDevice = new QFile(filename);
        reader.reset(new VCFVariantReader(mProgressDevice));

    }
    if (info.suffix() == "gz")
    {
        mProgressDevice = new QuaGzipFile(filename);
        reader.reset(new VCFVariantReader(mProgressDevice));
    }

    if (reader.isNull())
        return false;

    // Start import
    qInfo()<<"Start Importing "<<filename <<"";

    QElapsedTimer timer;
    timer.start();

    createProject(info.baseName());
    createLinks();
    createFile(filename);
    createMetadatas(reader.data());
    createSample(reader.data());
    createFields(reader.data());
    createGenotypeFields(reader.data());
    createVariants(reader.data());
    createGenotypes(reader.data());

    qInfo()<< "Import done in " << timer.elapsed() << "milliseconds";

    emit importRangeChanged(0,1);
    emit importProgressChanged(1,QString("Done in %1 ms").arg(timer.elapsed()));

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
        field.setCategory(query.value("category").toString());
        field.setExpression(QString("%2").arg(field.colname().toLower()));

        fields.append(field);
    }
    return fields;
}
//-------------------------------------------------------------------------------

QList<Field> SqliteManager::genotypeFields(const Sample& sample) const
{
    QList<Field> fields;
    QSqlQuery query(QStringLiteral("SELECT * FROM `genotype_fields`"));
    while(query.next())
    {
        Field field;
        field.setId(query.value("id").toInt());
        field.setColname(query.value("colname").toString());
        field.setName(query.value("name").toString());
        field.setDescription(query.value("description").toString());
        field.setType(query.value("type").toString());
        field.setCategory(query.value("category").toString());
        field.setExpression(QString("sample[\"%1\"].%2").arg(sample.name(),field.name().toLower()));

        fields.append(field);
    }
    return fields;
}

//-------------------------------------------------------------------------------
QList<VariantLink> SqliteManager::links() const
{
    QList<VariantLink> links;
    QSqlQuery query(QStringLiteral("SELECT * FROM `links`"));
    while(query.next())
    {
        VariantLink link;
        link.setId(query.value("id").toInt());
        link.setName(query.value("name").toString());
        link.setRawUrl(query.value("url").toString());

        QPixmap pix;
        pix.loadFromData(query.value("icon").toByteArray());
        link.setIcon(QIcon(pix));
        links.append(link);
    }
    return links;
}

//-------------------------------------------------------------------------------
QList<VariantSelection> SqliteManager::variantSelections() const
{

    QList<VariantSelection> list;
    QSqlQuery query("SELECT * FROM sqlite_master WHERE type = 'view'");
    while (query.next())
    {
        VariantSelection s = VariantSelection();
        s.setName(query.record().value("tbl_name").toString());
        s.setSql(query.record().value("sql").toString());
        list.append(s);

    }

    for (VariantSelection &s : list)
        s.setCount(variantsCount(s.name()));


    return list;

}
//-------------------------------------------------------------------------------
QStringList SqliteManager::variantSelectionNames() const
{
    QStringList out;
    for (const VariantSelection& s : variantSelections())
        out.append(s.name());
    return out;
}
//-------------------------------------------------------------------------------
QHash<QString, QVariant> SqliteManager::metadatas() const
{
    QHash<QString, QVariant> hash;

    QSqlQuery query("SELECT * FROM filemetas");
    while (query.next())
        hash.insert(query.record().value("key").toString(), query.record().value("value"));

    return hash;

}
//-------------------------------------------------------------------------------
bool SqliteManager::createSelectionFromExpression(const QString &newtable, const QString &rawExpression, CompareMode mode)
{
    qDebug()<<Q_FUNC_INFO<<" create expression ";

    QRegularExpression exp("[^\\-+&\\(\\)\\s&]+");
    QRegularExpressionMatchIterator it = exp.globalMatch(rawExpression);
    QStringList tables = variantSelectionNames();
    tables.append("variants");

    QString raw = rawExpression.simplified();
    while (it.hasNext())
    {
        QRegularExpressionMatch match = it.next();
        QString table = match.captured();

        if (!tables.contains(table))
        {
            qDebug()<<Q_FUNC_INFO<<" wrong expression, unknown table "+table;
            return false;
        }

        if (mode == CompareMode::SiteMode)
            raw = raw.replace(table, QString("SELECT chr, pos FROM `%1`").arg(table));

        if (mode == CompareMode::VariantMode)
            raw = raw.replace(table, QString("SELECT chr, pos, ref, alt FROM `%1`").arg(table));
    }

    raw = raw.replace("+", " UNION ");
    raw = raw.replace("-", " EXCEPT ");
    raw = raw.replace("&", " INTERSECT ");

    QSqlQuery query;
    query.exec(QString("DROP VIEW IF EXISTS %1").arg(newtable));


    if (mode == CompareMode::SiteMode)
        query.prepare(QString("CREATE VIEW %1 AS SELECT variants.* FROM variants, (%2) as t WHERE t.chr=variants.chr AND t.pos = variants.pos").arg(newtable,raw));

    if (mode == CompareMode::VariantMode)
        query.prepare(QString("CREATE VIEW %1 AS SELECT variants.* FROM variants, (%2) as t WHERE t.chr=variants.chr AND t.pos = variants.pos AND t.ref = variants.ref AND t.alt = variants.alt").arg(newtable,raw));


    if (!query.exec())
    {
        qDebug()<<query.lastError().text();
        qDebug()<<query.lastQuery();
    }

    qDebug()<<query.lastQuery();


    return true;

}
//-------------------------------------------------------------------------------
bool SqliteManager::removeSelection(const QString &name)
{
    QSqlQuery query;
    if (!query.exec(QString("DROP VIEW IF EXISTS %1").arg(name)))
    {
        qDebug()<<query.lastQuery();
        qDebug()<<query.lastError().text();
        return false;
    }

    return true;
}
//-------------------------------------------------------------------------------
bool SqliteManager::removeLink(const VariantLink &link)
{
    if (!link.exists())
        return false;

    QSqlQuery query;
    if (!query.exec(QString("DELETE FROM `links` WHERE id=%1").arg(link.id())))
    {
        qDebug()<<query.lastQuery();
        qDebug()<<query.lastError().text();
        return false;
    }

    return true;
}
//-------------------------------------------------------------------------------
bool SqliteManager::saveLink(VariantLink &link)
{
    QSqlQuery query;
    if (!link.exists())
        query.prepare( "INSERT INTO `links` (name, url, icon) VALUES (:name, :url, :icon)" );
    else
        query.prepare(QStringLiteral("UPDATE `links` SET name = :name , url = :url , icon = :icon WHERE id =%1").arg(link.id()));


    query.bindValue(":name", link.name());
    query.bindValue(":url", link.rawUrl());
    query.bindValue(":icon", iconToData(link.icon()));



    if (!query.exec())
    {
        qDebug()<<Q_FUNC_INFO<<" cannot save/update link "<<query.lastError().text();
        qDebug()<<query.lastQuery();
        return false;
    }

    if (!link.exists())
        link.setId(query.lastInsertId().toInt());

    return true;
}
//-------------------------------------------------------------------------------
QSqlQuery SqliteManager::variants(const VariantQuery &query) const
{

    return QSqlQuery(query.toSql(this));
}
//-------------------------------------------------------------------------------
int SqliteManager::variantsCount(const VariantQuery &query) const
{
    VariantQuery q = query;
    // set no limit ..
    q.setLimit(0);
    q.setColumns({"id"});

    QString sql = QString("SELECT COUNT(*) as 'count' FROM (%1)").arg(q.toSql(this));
    qDebug()<<sql;

    QSqlQuery countQuery;
    if (!countQuery.exec(sql))
    {
        qDebug()<<countQuery.lastQuery();
        qDebug()<<countQuery.lastError().text();
    }

    countQuery.next();
    return countQuery.record().value("count").toInt();

}
//-------------------------------------------------------------------------------
int SqliteManager::variantsCount(const QString &table) const
{
    VariantQuery query;
    query.setTable(table);
    query.setGroupBy({"chr","pos","ref","alt"});
    return variantsCount(query);
}
//-------------------------------------------------------------------------------

bool SqliteManager::variantsTo(const VariantQuery &query, const QString &tablename, const QString &description)
{
    Q_UNUSED(description)
    VariantQuery q = query;
    q.setLimit(0);
    q.setGroupBy({});
    q.setColumns({"*"});

    QSqlQuery viewQuery;
    viewQuery.exec(QString("DROP VIEW IF EXISTS %1").arg(tablename));

    if (!viewQuery.exec(QString("CREATE VIEW %1 AS %2").arg(tablename).arg(q.toSql(this))))
    {
        qDebug()<<viewQuery.lastQuery();
        qDebug()<<viewQuery.lastError().text();
        return false;
    }

    return true;
}

//-------------------------------------------------------------------------------
Variant SqliteManager::variant(int variantId) const
{
    QSqlQuery query;
    query.prepare(QStringLiteral("SELECT chr,rs,pos,ref,alt FROM variants WHERE id=:id"));
    query.bindValue(":id", variantId);

    if (!query.exec())
    {
        qDebug()<<Q_FUNC_INFO<<query.lastQuery();
        qDebug()<<Q_FUNC_INFO<<query.lastError().text();
    }

    query.next();
    QString chr = query.record().value("chr").toString();
    quint64 pos = query.record().value("pos").toInt();
    QString rs = query.record().value("rs").toString();
    QString ref = query.record().value("ref").toString();
    QString alt = query.record().value("alt").toString();

    qDebug()<<variantId<<" "<<query.lastQuery();
    qDebug()<<chr<<" "<<pos<<" "<<ref<<" "<<alt;

    Variant v =  Variant(chr,pos,ref, alt);
    v.setRsId(rs);

    return v;
}


//-------------------------------------------------------------------------------
QFuture<bool> SqliteManager::asyncImportFile(const QString &filename)
{

    return QtConcurrent::run(this, &SqliteManager::importFile, filename);

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

void SqliteManager::createFile(const QString &filename)
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
    query.bindValue(3, SqliteManager::md5sum(filename));


    if (!query.exec())
    {
        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
    }
}
//-------------------------------------------------------------------------------
void SqliteManager::createMetadatas(AbstractVariantReader *reader)
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
//-------------------------------------------------------------------------------
void SqliteManager::createLinks()
{
    qInfo()<<"Import Links";
    emit importProgressChanged(0,QString("Create defaults Links"));

    QSqlQuery query;
    query.exec(QStringLiteral("DROP TABLE IF EXISTS `links`"));
    query.exec(QStringLiteral("CREATE TABLE `links` ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name TEXT NOT NULL,"
                              "url TEXT NOT NULL,"
                              "icon BLOB"
                              ")"));


    VariantLink demo("IGV",QString("http://localhost:60151/goto?locus=$CHROM:$POS"),QIcon(":/on.png"));
    saveLink(demo);

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

void SqliteManager::createGenotypeFields(AbstractVariantReader *reader)
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
//-------------------------------------------------------------------------------
void SqliteManager::createVariants(AbstractVariantReader *reader)
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
        emit importRangeChanged(0, mProgressDevice->size());
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
//-------------------------------------------------------------------------------
void SqliteManager::createGenotypes(AbstractVariantReader *reader)
{
    qDebug()<<"Import Genotypes";

    if (samples().isEmpty())
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
//-------------------------------------------------------------------------------
QByteArray SqliteManager::md5sum(const QString &filename)
{
    QByteArray out;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QCryptographicHash hash(QCryptographicHash::Md5);
        if (hash.addData(&file))
            out = hash.result();
        else
            qWarning()<<Q_FUNC_INFO<<"cannot hash file "<<filename;

    }
    file.close();
    return out.toHex();

}
//-------------------------------------------------------------------------------
QByteArray SqliteManager::iconToData(const QIcon &icon)
{
    QByteArray inByteArray;
    QBuffer inBuffer(&inByteArray);
    inBuffer.open(QIODevice::WriteOnly);
    icon.pixmap(32,32).save(&inBuffer,"PNG");
    inBuffer.close();

    return inByteArray;

}
//-------------------------------------------------------------------------------



}
