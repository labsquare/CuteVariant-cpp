#include "querybuilder.h"

namespace cvar {

QueryBuilder::QueryBuilder(const QStringList &columns, const QString &table, const QString &condition)
    :mColumns(columns), mTable(table),mCondition(condition)
{

}

QString QueryBuilder::toSql() const
{

    if (columns().isEmpty() || table().isEmpty())
        qWarning()<<Q_FUNC_INFO<<"no columns or table set";

    QString q = QString("SELECT %1 FROM %2").arg(quote(columns()).join(","), quote(table()));

    if (!condition().isEmpty())
        q += " WHERE "+condition();

    if (!groupBy().isEmpty())
        q+= " GROUP BY "+quote(groupBy());


    if (!mColumnsOrder.isEmpty())
    {
        QStringList orders;

        for (const auto& i : mColumnsOrder)
        {
            orders.append(QString("%1 %2")
                          .arg(quote(i.first))
                          .arg(i.second == Qt::AscendingOrder ? "ASC": "DESC"));
        }

       q += " ORDER BY " + orders.join(",");
    }



    return q;
}

void QueryBuilder::addColumn(const QString &col)
{
    mColumns.append(col);
}

void QueryBuilder::addSortColumns(const QString &col, Qt::SortOrder order)
{
    mColumnsOrder.append(qMakePair(col,order));
}


QStringList QueryBuilder::columns() const
{
    return mColumns;
}

void QueryBuilder::setColumns(const QStringList &columns)
{
    mColumns = columns;
}

QString QueryBuilder::table() const
{
    return mTable;
}

void QueryBuilder::setTable(const QString &table)
{
    mTable = table;
}

QString QueryBuilder::condition() const
{
    return mCondition;
}

void QueryBuilder::setCondition(const QString &condition)
{
    mCondition = condition;
}

QString QueryBuilder::groupBy() const
{
    return mGroupBy;
}

void QueryBuilder::setGroupBy(const QString &groupBy)
{
    mGroupBy = groupBy;
}

View QueryBuilder::createView(const QString& name, const QString& description) const
{
    QString qv = "SELECT rowid, * FROM " + quote(table());

    if (!condition().isEmpty())
        qv += " WHERE " + condition();

    View view(name, description, mCountCache);
    view.setSql(qv);

    return view;

}

QString QueryBuilder::quote(const QString &word)
{
    return "`" + word + "`";

}

QStringList QueryBuilder::quote(const QStringList &words)
{
    QStringList out = words;
    for (QString& i : out)
        i = quote(i);

    return out;

}



}
