#include "viewdatamapper.h"

namespace cvar{

ViewDataMapper::ViewDataMapper()
    :DataMapper<View, ViewDataMapper>("views")
{

    addColumn("name",DataColumn::Text, "NOT NULL");
    addColumn("count",DataColumn::Integer, "DEFAULT 0");
    addColumn("query",DataColumn::Text);
    addColumn("comment",DataColumn::Text);

}

View ViewDataMapper::fromSql(const QSqlRecord &record) const
{

}

QHash<QString, QVariant> ViewDataMapper::toSql(const View &record) const
{

}

}
