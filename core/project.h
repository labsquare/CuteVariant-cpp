#ifndef PROJECT_H
#define PROJECT_H

#include <QtCore>
#include <QtSql>
#include <QDebug>
#include "field.h"
#include "region.h"

class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(const QString& databasePath, QObject *parent = 0);
    /*!
     * \brief setDatabasePath
     * \param filename
     * set Sqlite database path
     */
    void setDatabasePath(const QString& filename);

    // Not yet implemented
    void importVCF(const QString& path);

    static QList<Field> fields();

    static QSqlQuery variantQuery(const QStringList& colnames  = QStringList(),
                           const QString& condition     = QString(),
                           const QList<Region>& regions = QList<Region>());



private:
    QString mName;
    QSqlDatabase mDb;
};



#endif // PROJECT_H
