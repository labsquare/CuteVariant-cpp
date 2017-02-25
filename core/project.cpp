#include "project.h"

Project::Project(const QString &databasePath, QObject *parent): QObject(parent)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    setDatabasePath(databasePath);

    if (!mDb.open())
        qDebug()<<"cannot open database";


}

void Project::setDatabasePath(const QString &filename)
{
    mDb.setDatabaseName(filename);
}

void Project::importVCF(const QString &path)
{
    // TODO
    // Use the python version for now
}

QList<Field> Project::fields() const
{
    QList<Field> fields;
    QSqlQuery query;

    if (!query.exec("SELECT * FROM fields"))
    {
        qDebug()<<Q_FUNC_INFO<<query.lastError().text();
        return fields;
    }

    while (query.next())
    {
        int sqlId    = query.record().value("id").toInt();
        QString name = query.record().value("colname").toString();
        QString desc = query.record().value("desc").toString();
        fields.append(Field(sqlId,name, desc));
    }
}
