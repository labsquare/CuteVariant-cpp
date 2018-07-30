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


    // samples

    /*!
     * \brief samples
     * \return samples list from sqlite
     */
    QList<Sample> samples() const;



    // regions
    QList<Region> regions(int bedId) const;



    // Links
    QList<VariantLink> links() const;
    bool setLinks(QList<VariantLink>& links);
    bool removeLink(const VariantLink& link);
    bool addLink(VariantLink& link);



private:
    Project();
    QSqlDatabase mSqlDb;
    static Project * mInstance;



};
}
#endif // PROJECT_H
