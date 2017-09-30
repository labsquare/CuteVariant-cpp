#ifndef PROJECT_H
#define PROJECT_H
#include <QtCore>
#include <QtSql>
#include "sqlitemanager.h"

#define cutevariant cvar::Project::i()

namespace cvar {
class QueryBuilder;
class SqliteManager;
class Project
{
public:
    ~Project();


    static Project * i();

    void setDatabasePath(const QString& path);
    void importFile(const QString& filename);
    SqliteManager * sqliteManager();


private:
    Project();

    QSqlDatabase mSqlDb;
    SqliteManager * mSqliteManager;
    static Project * mInstance;



};
}
#endif // PROJECT_H
