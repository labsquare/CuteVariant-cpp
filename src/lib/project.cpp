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

    QFileInfo info(path);
    mSqliteManager->createProject(info.baseName());
}

void Project::importFile(const QString &filename)
{

    mSqliteManager->importFile(filename);
}

SqliteManager *Project::sqliteManager()
{
    return mSqliteManager;
}

}
