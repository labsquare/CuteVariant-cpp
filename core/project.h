#ifndef PROJECT_H
#define PROJECT_H

#include <QtCore>
#include <QtSql>
#include <QDebug>
#include "vcfimporter.h"
class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(const QString& databasePath, QObject *parent = 0);

    void setDatabasePath(const QString& filename);
    bool createSchema();
    void importVCF(const QStringList& paths);
    void importVCF(const QString& path);

private:
    QString mName;
    QSqlDatabase mDb;

    VcfImporter * mImporter;



};

#endif // PROJECT_H
