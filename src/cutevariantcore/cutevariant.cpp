#include "cutevariant.h"

namespace cvar {

CuteVariant * CuteVariant::mInstance = nullptr;

CuteVariant::CuteVariant(QObject *parent)
    :QObject(parent)
{

    mImporter = new Importer(this);

    // map importer signal to cutevariant
    connect(mImporter,SIGNAL(importProgressChanged(int,QString)), this,SIGNAL(importProgressChanged(int,QString)));
    connect(mImporter,SIGNAL(importRangeChanged(int,int)), this,SIGNAL(importRangeChanged(int,int)));


}
CuteVariant::~CuteVariant()
{

        delete mImporter;
}

CuteVariant *CuteVariant::i()
{
    if (!mInstance)
        mInstance = new CuteVariant();

    return mInstance;
}

bool CuteVariant::setDatabasePath(const QString &path)
{
    mSqlDb = QSqlDatabase::addDatabase("QSQLITE");
    mSqlDb.setDatabaseName(path);
    return mSqlDb.open();

}
//=================== SAMPLES  =====================
QList<Sample> CuteVariant::samples() const
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

//=================== FIELDS  =====================

QList<Field> CuteVariant::fields() const
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
//----------------------------------------------------
QList<Field> CuteVariant::genotypeFields() const
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

        // TODO
        // field.setExpression(QString("genotype(\"%1\").%2").arg(sample.name(),field.name().toLower()));

        fields.append(field);
    }
    return fields;
}
//----------------------------------------------------
QList<View> CuteVariant::views() const
{

    QList<View> list;
    QSqlQuery query("SELECT * FROM sqlite_master WHERE type = 'view'");
    while (query.next())
    {
        View s = View();
        s.setName(query.record().value("tbl_name").toString());
        s.setSql(query.record().value("sql").toString());
        list.append(s);

    }

    // TODO count is slow ! Need to store somewhere
    // create View tables
    for (View &s : list)
        s.setCount(-1);

    return list;
}
//----------------------------------------------------
bool CuteVariant::addView(const View &view)
{
    QSqlQuery viewQuery;
    viewQuery.exec(QString("DROP VIEW IF EXISTS %1").arg(view.name()));

    if (!viewQuery.exec(QString("CREATE VIEW %1 AS %2").arg(view.name()).arg(view.sql())))
    {
        qDebug()<<viewQuery.lastQuery();
        qDebug()<<viewQuery.lastError().text();
        return false;
    }

    qDebug()<<viewQuery.lastQuery();
    qDebug()<<viewQuery.lastError().text();

    return true;
}
//----------------------------------------------------
bool CuteVariant::addViewFromExpression(const QString &name, const QString &expression, CuteVariant::CompareMode mode)
{
    qDebug()<<Q_FUNC_INFO<<" create expression ";

    QRegularExpression exp("[^\\-+&\\(\\)\\s&]+");
    QRegularExpressionMatchIterator it = exp.globalMatch(expression);
    QStringList tables = viewNames();
    tables.append("variants");

    QString raw = expression.simplified();
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
    query.exec(QString("DROP VIEW IF EXISTS %1").arg(name));


    if (mode == CompareMode::SiteMode)
        query.prepare(QString("CREATE VIEW %1 AS SELECT variants.* FROM variants, (%2) as t WHERE t.chr=variants.chr AND t.pos = variants.pos").arg(name,raw));

    if (mode == CompareMode::VariantMode)
        query.prepare(QString("CREATE VIEW %1 AS SELECT variants.* FROM variants, (%2) as t WHERE t.chr=variants.chr AND t.pos = variants.pos AND t.ref = variants.ref AND t.alt = variants.alt").arg(name,raw));


    if (!query.exec())
    {
        qDebug()<<query.lastError().text();
        qDebug()<<query.lastQuery();
    }
    qDebug()<<query.lastQuery();

    return true;
}
//----------------------------------------------------
bool CuteVariant::removeView(const QString &name) const
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
//----------------------------------------------------
QStringList CuteVariant::viewNames() const
{
    QStringList out;
    out += "variants";
    for (const View& s : views())
        out.append(s.name());
    return out;
}
//----------------------------------------------------
Variant CuteVariant::variant(int id) const
{
    QSqlQuery query;
    query.prepare(QStringLiteral("SELECT chr,rs,pos,ref,alt FROM variants WHERE id=:id"));
    query.bindValue(":id", id);

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

    qDebug()<<id<<" "<<query.lastQuery();
    qDebug()<<chr<<" "<<pos<<" "<<ref<<" "<<alt;

    Variant v =  Variant(chr,pos,ref, alt);
    v.setRsId(rs);

    return v;
}
//----------------------------------------------------
int CuteVariant::variantsCount(const VariantQuery &query)
{
    VariantQuery q = query;
    // set no limit ..
    q.setLimit(0);
    q.setColumns({"id"});

    QString sql = QString("SELECT COUNT(1) as 'count' FROM (%1)").arg(q.toSql());

    QSqlQuery countQuery;
    if (!countQuery.exec(sql))
    {
        qDebug()<<countQuery.lastQuery();
        qDebug()<<countQuery.lastError().text();
    }

    countQuery.next();

    return (countQuery.record().value("count").toInt());
}
//----------------------------------------------------
int CuteVariant::viewCount(const QString &view)
{
    // TODO :: to slow ...
    VariantQuery query;
    query.setTable(view);
    query.setGroupBy({"chr","pos","ref","alt"});
    return -1;
}
//=================== METADATAS =========================

QHash<QString, QVariant> CuteVariant::metadatas() const
{
    QHash<QString, QVariant> hash;

    QSqlQuery query("SELECT * FROM filemetas");
    while (query.next())
        hash.insert(query.record().value("key").toString(), query.record().value("value"));

    return hash;
}

QList<BedFile> CuteVariant::bedFiles() const
{
    QList<BedFile> files;
    QSqlQuery query(QStringLiteral("SELECT * FROM `bedfiles`"));
    while(query.next())
    {
        BedFile file;
        file.setId(query.value("id").toInt());
        file.setFilename(query.value("filename").toString());
        file.setCount(query.value("count").toInt());
        files.append(file);
    }
    return files;
}

//=================== LINKS =========================
QList<VariantLink> CuteVariant::links() const
{
    QList<VariantLink> list;

    QSettings settings;
    int size = settings.beginReadArray("links");

    for (int i=0; i<size; ++i)
    {
        settings.setArrayIndex(i);
        VariantLink link;
        link.setName(settings.value("name").toString());
        link.setRawUrl(settings.value("rawUrl").toString());
        link.setIcon(settings.value("icon").value<QIcon>());

        list.append(link);
    }
    settings.endArray();

    return list;
}
//----------------------------------------------------
bool CuteVariant::removeLink(const VariantLink &link)
{
    QList<VariantLink> list = links();
    list.removeOne(link);
    return setLinks(list);

}
//----------------------------------------------------
bool CuteVariant::addLink(VariantLink &link)
{
    QList<VariantLink> list = links();
    list.append(link);
    return setLinks(list);
}
//----------------------------------------------------
QFuture<bool> CuteVariant::importFile(const QString &filename, VariantReaderFactory::Format format)
{
    QString dbFilename = filename + ".db";

   if (!setDatabasePath(dbFilename)){
       qDebug()<<Q_FUNC_INFO<<"cannot create database path";
        return QFuture<bool>();
   }

   return mImporter->asyncImport(filename, format);
}
//----------------------------------------------------
//SqliteManager *CuteVariant::sqlite()
//{
//    return mSqliteManager;
//}

bool CuteVariant::setLinks(QList<VariantLink> &links)
{
    QSettings settings;
    settings.beginWriteArray("links");
    for (int i=0; i<links.size(); ++i)
    {

        settings.setArrayIndex(i);
        settings.setValue("name", links[i].name());
        settings.setValue("rawUrl", links[i].rawUrl());
        settings.setValue("icon", links[i].icon());
    }
    settings.endArray();

    return true;
}
//=================== UTILS =========================

QByteArray CuteVariant::md5sum(const QString &filename)
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
//----------------------------------------------------

QByteArray CuteVariant::iconToData(const QIcon &icon)
{
    QByteArray inByteArray;
    QBuffer inBuffer(&inByteArray);
    inBuffer.open(QIODevice::WriteOnly);
    icon.pixmap(32,32).save(&inBuffer,"PNG");
    inBuffer.close();

    return inByteArray;
}
//----------------------------------------------------
}
