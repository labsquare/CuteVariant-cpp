#include "sampledatamapper.h"
#include "sample.h"
namespace cvar {

SampleDataMapper::SampleDataMapper()
    :DataMapper<Sample, SampleDataMapper>("samples")
{

    addColumn("name", DataColumn::Text, "NOT NULL");

}

QHash<QString, QVariant> SampleDataMapper::toSql(const Sample &record) const
{
    return
    {
        {"id", record.id()},
        {"name",record.name()}
    };
}

Sample SampleDataMapper::fromSql(const QSqlRecord &record) const
{
    Sample sample;
    sample.setId(record.value("id").toInt());
    sample.setName(record.value("name").toString());
    return sample;
}


//bool SampleDataMapper::insert(const QList<Sample> &records) const
//{
//    QSqlQuery query;
//    query.prepare(QStringLiteral("INSERT INTO `samples` (name) VALUES (:name)"));

//    for (const Sample& record : records)
//    {

//        query.bindValue("name", record.name());


//        if (!query.exec())
//        {
//            qWarning()<<Q_FUNC_INFO<<query.lastQuery();
//            qWarning()<<Q_FUNC_INFO<<query.lastError().text();
//            return false;
//        }
//    }
//    return true;
//}

//bool SampleDataMapper::update(const Sample &record) const
//{

//    if (record.id() == -1)
//    {
//        qWarning()<<Q_FUNC_INFO<<"no record id";
//        return false;
//    }

//    QSqlQuery query;
//    query.prepare(QStringLiteral("UPDATE `samples` SET name = :name WHERE id=:id"));

//    query.bindValue("name", record.name());
//    query.bindValue("name", record.id());

//    if (!query.exec())
//    {
//        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
//        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
//        return false;
//    }

//    return true;
//}

//bool SampleDataMapper::remove(const Sample &record) const
//{
//    if (record.id() == -1)
//    {
//        qWarning()<<Q_FUNC_INFO<<"no record id";
//        return false;
//    }

//    QSqlQuery query;
//    query.prepare(QStringLiteral("DELETE FROM `table` WHERE id=:id"));
//    query.bindValue("name", record.id());

//    if (!query.exec())
//    {
//        qWarning()<<Q_FUNC_INFO<<query.lastQuery();
//        qWarning()<<Q_FUNC_INFO<<query.lastError().text();
//        return false;
//    }

//    return true;
//}

//Sample SampleDataMapper::fromSql(const QSqlRecord &record) const
//{

//    Sample sample;
//    sample.setId(record.value("id").toInt());
//    sample.setName(record.value("name").toString());

//    return sample;
//}

//QHash<QString, QVariant> SampleDataMapper::bind(const Sample &record) const
//{

//    return
//    {
//        {"id", record.id()},
//        {"name",record.name()}
//    };

//}

//bool SampleDataMapper::createTable() const
//{
//    QSqlQuery query;
//    query.exec(QStringLiteral("DROP TABLE IF EXISTS samples"));
//    query.exec(QStringLiteral("CREATE TABLE samples ("
//                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
//                              "name TEXT NOT NULL"
//                              ")"));
//    query.exec(QStringLiteral("CREATE INDEX samples_idx ON samples (id)"));

//}





}
