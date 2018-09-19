#include "variantquerybuilder.h"

namespace cvar {
VariantQueryBuilder::VariantQueryBuilder()
{

}

VariantQueryBuilder::VariantQueryBuilder(const QStringList &columns, const QString &table)
    :mColumns(columns), mTable(table)
{

}

VariantQueryBuilder::VariantQueryBuilder(const QStringList &columns, const QString &table, const QString &conditions)
    :mColumns(columns), mTable(table), mCondition(conditions)
{

}

bool VariantQueryBuilder::isValid() const
{
    //TODO check valid query

    return true;


}

const QStringList& VariantQueryBuilder::columns() const
{
    return mColumns;
}

void VariantQueryBuilder::setColumns(const QStringList &columns)
{
    mColumns.clear();
    for (const QString& col: columns)
    {
        mColumns.append(col.simplified());
    }
}

const QString& VariantQueryBuilder::table() const
{
    return mTable;
}

void VariantQueryBuilder::setTable(const QString &table)
{
    mTable = table;
}

const QString &VariantQueryBuilder::condition() const
{
    return mCondition;
}

void VariantQueryBuilder::setCondition(const QString &condition)
{
    mCondition = condition;
}

int VariantQueryBuilder::offset() const
{
    return mOffset;
}

void VariantQueryBuilder::setOffset(int offset)
{
    mOffset = offset;
}

int VariantQueryBuilder::limit() const
{
    return mLimit;
}

void VariantQueryBuilder::setLimit(int limit)
{
    mLimit = limit;
}

QStringList VariantQueryBuilder::groupBy() const
{
    return mGroupBy;
}

void VariantQueryBuilder::setGroupBy(const QStringList &groupBy)
{
    mGroupBy = groupBy;
}

QString VariantQueryBuilder::toSql() const
{

    //    // the sql query to return
    QString s_query;

    // select statement
    QString s_select = "SELECT `rowid`, " + sqlColumns().join(",");

    // where statement
    QString s_where = !sqlCondition().isEmpty() ? " WHERE "+sqlCondition() : QString();

    // from statement
    QString s_from = " FROM "+sqlTableName();

    //    // left join statement
    //    QString s_leftJoin;

    // group by statement
    QString s_groupBy = sqlGroupBy();

    // order by statement
    QString s_orderBy = sqlOrderBy();

    // limt offset statement
    QString s_limitOffset = sqlLimitOffset();


    // add extra fields for group by
    //    if (!groupBy().isEmpty())
    //        s_select += QString(" ,COUNT(%1.id) as 'count', group_concat(%1.id) as 'childs' ").arg(table());

    //    // add region
    //    if (!region().isEmpty()){
    //        s_from += ","+sqlRegion();

    //        if (s_where.isEmpty())
    //            s_where.append(QString(" WHERE %1.pos BETWEEN %2.start AND %2.end AND %1.chr = %2.chr").arg(sqlTableName(), sqlRegion()));
    //        else
    //            s_where.append(QString(" AND %1.pos BETWEEN %2.start AND %2.end AND %1.chr = %2.chr").arg(sqlTableName(), sqlRegion()));


    //    }
    //    // Create query

    //    qDebug()<<"select:"<<s_select;
    //    qDebug()<<"from:"<<s_from;
    //    qDebug()<<"leftJoin:"<<s_leftJoin;
    //    qDebug()<<"where:"<<s_where;
    //    qDebug()<<"groupBy:"<<s_groupBy;
    //    qDebug()<<"orderBy:"<<s_orderBy;
    //    qDebug()<<"limitOffset:"<<s_limitOffset;


    s_query = s_select + s_from + s_where + s_groupBy + s_orderBy + s_limitOffset;






    //    //    // SELECT columns FROM table LEFT JOIN ON ..
    //    //    if (!joinSamples.isEmpty())
    //    //        query.append(joinSamples.join(" "));

    //    //    // SELECT columns FROM table WHERE conditions
    //    //    if (!where.isEmpty())
    //    //        query.append(QString(" WHERE %1 ").arg(where));


    //    //    // check region
    //    //    // TODO check if region exists
    //    //    if (!mBed.isEmpty())
    //    //    {
    //    //        if (where.isEmpty())
    //    //            query.append(QString(" WHERE %1.pos BETWEEN regions.start AND regions.end AND %1.chr = regions.chr").arg(tableName));
    //    //        else
    //    //            query.append(QString(" AND %1.pos BETWEEN regions.start AND regions.end AND %1.chr = regions.chr").arg(tableName));
    //    //    }



    //    //    // SELECT columns FROM table WHERE condition GROUP BY
    //    //    // TODO ugly
    //    //    QStringList gp = groupBy();
    //    //    for (QString& i : gp )
    //    //        i.prepend(tableName+".");

    //    //    if (!groupBy().isEmpty())
    //    //        query.append(QString(" GROUP BY %1 ").arg(gp.join(",")));

    //    //    if (!orderBy().isEmpty())
    //    //        query.append(QString( " ORDER BY %1 %2 ").arg(orderBy().join(",")).arg(mSortOder==Qt::AscendingOrder ? "ASC" : "DESC"));

    //    //    // LIMIT and OFFSET
    //    //    if (limit() > 0)
    //    //        query.append(QString(" LIMIT %1 OFFSET %2").arg(limit()).arg(offset()));

    return s_query.simplified();
}

View VariantQueryBuilder::toView(const QString &name, const QString &description)
{
    VariantQueryBuilder n = *(this);
    n.setColumns({"*"});
    View view(name,description, 0);


    return view;

}

Qt::SortOrder VariantQueryBuilder::sortOder() const
{
    return mSortOder;
}

void VariantQueryBuilder::setSortOrder(Qt::SortOrder sortOder)
{
    mSortOder = sortOder;
}

void VariantQueryBuilder::setNoLimit()
{
    setLimit(0);
    setOffset(0);
}

const QString &VariantQueryBuilder::region() const
{
    return mRegion;
}

void VariantQueryBuilder::setRegion(const QString &region)
{
    mRegion = region;
}

QStringList VariantQueryBuilder::orderBy() const
{
    return mOrderBy;
}

void VariantQueryBuilder::setOrderBy(const QStringList &orderBy)
{
    mOrderBy = orderBy;
}

const QStringList VariantQueryBuilder::sqlColumns() const
{
    QStringList out;
    std::transform(columns().begin(), columns().end(), std::back_inserter(out), [](const auto& i)
    {
        return "`"+i+"`";
    });

    return out;
}

const QString VariantQueryBuilder::sqlTableName() const
{
    if (table().isEmpty())
        return "'variants'";
    else
        return QString("`%1`").arg(table());
}

const QString VariantQueryBuilder::sqlCondition() const
{

    if (condition().isEmpty())
        return QString();
    return condition();
}

const QString VariantQueryBuilder::sqlOrderBy() const
{
    if (orderBy().isEmpty())
        return QString();
    else
        return QString( " ORDER BY `%1` %2 ").arg(orderBy().join(",")).arg(mSortOder==Qt::AscendingOrder ? "ASC" : "DESC");
}

const QString VariantQueryBuilder::sqlGroupBy() const
{
    if (!groupBy().isEmpty())
        return QString(" GROUP BY `%1` ").arg(groupBy().join(","));
    else
        return QString();
}

const QString VariantQueryBuilder::sqlLimitOffset() const
{
    if (limit() == 0)
        return QString();

    return QString(" LIMIT %1 OFFSET %2").arg(limit()).arg(offset());

}

const QString VariantQueryBuilder::sqlRegion() const
{
    if (region().isEmpty())
        return QString();

    return "bed_"+region();

}


QDebug operator<< (QDebug d, const VariantQueryBuilder &query)
{
    d<<"================================================\n";
    d<<"table\t"<<query.table()<<"\n";
    d<<"columns size\t"<<query.columns().size()<<"\n";
    d<<"columns\t"<<query.columns()<<"\n";
    d<<"condition\t"<<query.condition()<<"\n";
    d<<"bed\t"<<query.region()<<"\n";
    d<<"group by\t"<<query.groupBy()<<"\n";
    d<<"order by\t"<<query.orderBy()<<"\n";
    d<<"offset \t"<<query.offset()<<"\n";
    d<<"limit \t"<<query.limit()<<"\n";
    d<<"================================================\n";




    return d;
}



}
