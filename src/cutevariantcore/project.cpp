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
    mSqlDb = QSqlDatabase::addDatabase("QSQLITE");
    mSqlDb.setDatabaseName(path);
    if (!mSqlDb.open())
        qDebug()<<"cannot open database";

    //    QFileInfo info(path);
    //    mSqliteManager->createProject(info.baseName());
}

bool Project::importFile(const QString &filename)
{
    if (mSqlDb.isOpen())
        return mSqliteManager->importFile(filename);
    else{
        qDebug()<<"Cannot import. Database is not open";
        return false;
    }

}

SqliteManager *Project::sqlite()
{
    return mSqliteManager;
}

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

bool Project::removeLink(const VariantLink &link)
{
    QList<VariantLink> list = links();
    list.removeOne(link);
    return saveLinks(list);

}

bool Project::saveLink(VariantLink &link)
{
    QList<VariantLink> list = links();
    list.append(link);
    return saveLinks(list);
}

bool Project::saveLinks(QList<VariantLink> &links)
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


}
