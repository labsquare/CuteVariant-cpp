#include "project.h"

namespace cvar {

Project * Project::mInstance = nullptr;

Project::Project()
{
    mSqliteManager = new SqliteManager;
}

Importer *Project::importer()
{
    return mImporter;
}


Project::~Project()
{
    delete mSqliteManager;
}

Project *Project::i()
{
    if (!mInstance)
        mInstance = new Project();

    return mInstance;
}

void Project::setDatabasePath(const QString &path)
{
    //TODO Manage multi DB. 1 per project
    mSqlDb = QSqlDatabase::addDatabase("QSQLITE", "project");
    mSqlDb.setDatabaseName(path);
    if (!mSqlDb.open())
        qDebug()<<Q_FUNC_INFO<<"cannot open database";





}
//=================== SAMPLES  =====================
QList<Sample> Project::samples() const
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

QList<Field> Project::fields() const
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
QList<Field> Project::genotypeFields() const
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
QList<View> Project::views() const
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
bool Project::addView(const View &view)
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
bool Project::removeView(const QString &name) const
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
QStringList Project::viewNames() const
{
    QStringList out;
    out += "variants";
    for (const View& s : views())
        out.append(s.name());
    return out;
}
//----------------------------------------------------
Variant Project::variant(int id) const
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
int Project::viewCount(const QString &view)
{
    // TODO :: to slow ...
    VariantQuery query;
    query.setTable(view);
    query.setGroupBy({"chr","pos","ref","alt"});
    return -1;
}
//=================== METADATAS =========================

QHash<QString, QVariant> Project::metadatas() const
{
    QHash<QString, QVariant> hash;

    QSqlQuery query("SELECT * FROM filemetas");
    while (query.next())
        hash.insert(query.record().value("key").toString(), query.record().value("value"));

    return hash;
}

//=================== LINKS =========================
QList<VariantLink> Project::links() const
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
bool Project::removeLink(const VariantLink &link)
{
    QList<VariantLink> list = links();
    list.removeOne(link);
    return setLinks(list);

}
//----------------------------------------------------
bool Project::addLink(VariantLink &link)
{
    QList<VariantLink> list = links();
    list.append(link);
    return setLinks(list);
}

SqliteManager *Project::sqlite()
{
    return mSqliteManager;
}

bool Project::setLinks(QList<VariantLink> &links)
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

QByteArray Project::md5sum(const QString &filename)
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

QByteArray Project::iconToData(const QIcon &icon)
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
