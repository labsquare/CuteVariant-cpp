#include "project.h"

namespace core {
Project::Project()
{
    mSqlDb = QSqlDatabase::addDatabase("QSQLITE");
}

Project::Project(const QString &path)
    :Project()
{

    setDatabasePath(path);
}

void Project::setDatabasePath(const QString &path)
{

    mSqlDb.setDatabaseName(path);
    if (!mSqlDb.open())
        qDebug()<<"cannot open database";
}

void Project::importFile(const QString &filename)
{

    mImporter.importFile(filename);
}

}
