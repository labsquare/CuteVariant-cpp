#include "project.h"

namespace cvar {

Project * Project::mInstance = nullptr;

Project::Project()
{
    mSqliteManager = new SqliteManager;
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

    //    QFileInfo info(path);
    //    mSqliteManager->createProject(info.baseName());
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
//----------------------------------------------------
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
//----------------------------------------------------

}
