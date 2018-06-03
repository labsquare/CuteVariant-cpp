#ifndef PROJECT_H
#define PROJECT_H
#include <QtCore>
#include <QtSql>
#include <QSettings>
#include "variantlink.h"
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
    bool importFile(const QString& filename);
    SqliteManager * sqlite();

    QList<VariantLink> links() const;
    bool removeLink(const VariantLink& link);
    bool saveLink(VariantLink& link);
    bool saveLinks(QList<VariantLink>& links);



private:
    Project();

    QSqlDatabase mSqlDb;
    SqliteManager * mSqliteManager;
    static Project * mInstance;



};
}
#endif // PROJECT_H
