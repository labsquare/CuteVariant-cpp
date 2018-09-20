#include "viewdatamapper.h"

namespace cvar{

ViewDataMapper::ViewDataMapper()
    :DataMapper<View, ViewDataMapper>("views")
{

    addColumn("name",DataColumn::Text, "NOT NULL");
    addColumn("count",DataColumn::Integer, "DEFAULT 0");
    addColumn("sql",DataColumn::Text);
    addColumn("description",DataColumn::Text);

}

View ViewDataMapper::fromSql(const QSqlRecord &record) const
{

    View view;
    view.setName(record.value("name").toString());
    view.setDescription(record.value("description").toString());
    view.setSql(record.value("sql").toString());
    view.setCount(record.value("count").toInt());

    return view;

}

QHash<QString, QVariant> ViewDataMapper::toSql(const View &record) const
{
    return {
        {"name", record.name()},
        {"description", record.description()},
        {"sql", record.sql()},
        {"count", record.count()}
    };


}



bool ViewDataMapper::createView(const View &record) const
{
    QSqlQuery q;

    if (q.exec(QString("CREATE VIEW `%1` AS %2").arg(record.name(), record.sql())))
        return insertOne(record);
    else
    {
        qDebug()<<q.lastQuery();
        qDebug()<<q.lastError().text();
    }

    return false;

}



}
