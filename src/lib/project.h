#ifndef PROJECT_H
#define PROJECT_H
#include <QtCore>
#include <QtSql>
#include "variantimporter.h"

namespace core {
class Project
{
public:
    Project();
    Project(const QString& path);

    /*!
     * \brief setDatabasePath
     * set sqlite database path
     * \param path
     */
    void setDatabasePath(const QString& path);

    void importFile(const QString& filename);



private:
    QSqlDatabase mSqlDb;
    VariantImporter mImporter;

};
}
#endif // PROJECT_H
