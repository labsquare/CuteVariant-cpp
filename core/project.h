#ifndef PROJECT_H
#define PROJECT_H

#include <QtCore>
#include <QtSql>
#include <QDebug>
class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(const QString& databasePath, QObject *parent = 0);

    void setDatabasePath(const QString& filename);
    bool createSchema();

private:
    QString mName;
    QSqlDatabase mDb;



};

#endif // PROJECT_H
