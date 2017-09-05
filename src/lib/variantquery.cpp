#include "variantquery.h"

namespace cvar {
VariantQuery::VariantQuery()
{

}

VariantQuery::VariantQuery(const QStringList &columns, const QString &table)
    :mColumns(columns), mTable(table)
{

}

VariantQuery::VariantQuery(const QStringList &columns, const QString &table, const QString &conditions)
    :mColumns(columns), mTable(table), mCondition(conditions)
{

}

bool VariantQuery::isValid() const
{
    //TODO check valid VQL expression
    QRegularExpression exp1("SELECT .+");
    QRegularExpression exp2("SELECT .+ FROM .+");
    QRegularExpression exp3("SELECT .+ FROM .+ WHERE .+");

    return true;


}

QStringList VariantQuery::columns() const
{
    return mColumns;
}

void VariantQuery::setColumns(const QStringList &columns)
{
    mColumns = columns;
}

QString VariantQuery::table() const
{
    return mTable;
}

void VariantQuery::setTable(const QString &table)
{
    mTable = table;
}

QString VariantQuery::condition() const
{
    return mCondition;
}

void VariantQuery::setCondition(const QString &condition)
{
    mCondition = condition;
}

int VariantQuery::offset() const
{
    return mOffset;
}

void VariantQuery::setOffset(int offset)
{
    mOffset = offset;
}

int VariantQuery::limit() const
{
    return mLimit;
}

void VariantQuery::setLimit(int limit)
{
    mLimit = limit;
}

QStringList VariantQuery::groupBy() const
{
    return mGroupBy;
}

void VariantQuery::setGroupBy(const QStringList &groupBy)
{
    mGroupBy = groupBy;
}

QString VariantQuery::toSql(const SqliteManager *sql) const
{
    QString query;

    QString select     = table()+".id, "+columns().join(",");
    QString tableName  = table().isEmpty() ? "variants" : table();
    QString where      = condition();

    QStringList joinSamples;
    QStringList whereSamples;


    // get samples Ids
    QHash<QString, int> samplesIds;
    for (Sample s : sql->samples()){
        qDebug()<<s.name();
        samplesIds[s.name()] = s.id();
    }

    // Create join
    for (QString sample : detectSamplesFields())
    {

        joinSamples.append(QString(" LEFT JOIN genotypes as gt_%1 ON %2.id = gt_%1.variant_id ").arg(sample).arg(tableName));
        whereSamples.append(QString(" gt_%1.sample_id = %2 ").arg(sample).arg(samplesIds[sample]));
    }

    if (!joinSamples.isEmpty())
    {
        if (where.isEmpty())
            where = whereSamples.join(" AND ");
        else
            where.append("AND "+whereSamples.join(" AND "));
    }


    // add extra fields for group by
    if (!groupBy().isEmpty())
        select += QString(" ,COUNT(`%1`.id) as 'count', group_concat(`%1`.id) as 'childs' ").arg(tableName);


    // SELECT columns FROM table
    query = QString("SELECT %1 FROM %2").arg(select).arg(tableName);

    // SELECT columns FROM table LEFT JOIN ON ..
    if (!joinSamples.isEmpty())
        query.append(joinSamples.join(" "));

    // SELECT columns FROM table WHERE conditions
    if (!where.isEmpty())
        query.append(QString(" WHERE %1 ").arg(where));

    // SELECT columns FROM table WHERE condition GROUP BY
    if (!groupBy().isEmpty())
        query.append(QString(" GROUP BY %1 ").arg(groupBy().join(",")));

    if (!orderBy().isEmpty())
        query.append(QString( " ORDER BY %1 %2 ").arg(orderBy().join(",")).arg(mSortOder==Qt::AscendingOrder ? "ASC" : "DESC"));

    // LIMIT and OFFSET
    if (limit() > 0)
        query.append(QString(" LIMIT %1 OFFSET %2").arg(limit()).arg(offset()));

    return query;
}

QStringList VariantQuery::detectSamplesFields() const
{
    QSet<QString> sampleName;
    QRegularExpression exp (QStringLiteral("gt_(?<sample>\\w+).(?<field>\\w+)"));
    QString source = columns().join(" ") +" "+ condition();

    QRegularExpressionMatchIterator it = exp.globalMatch(source);

    while(it.hasNext())
    {
        QRegularExpressionMatch match = it.next();
        sampleName.insert(match.captured("sample"));
    }

    return sampleName.toList();
}

Qt::SortOrder VariantQuery::sortOder() const
{
    return mSortOder;
}

void VariantQuery::setSortOrder(Qt::SortOrder sortOder)
{
    mSortOder = sortOder;
}

void VariantQuery::setNoLimit()
{
    setLimit(0);
    setOffset(0);
}



QStringList VariantQuery::orderBy() const
{
    return mOrderBy;
}

void VariantQuery::setOrderBy(const QStringList &orderBy)
{
    mOrderBy = orderBy;
}

VariantQuery VariantQuery::fromVql(const QString &vql)
{
    VariantQuery query;

    QRegularExpression exp1("SELECT (?<columns>.+)");
    QRegularExpression exp2("SELECT (?<columns>.+) FROM (?<table>.+)");
    QRegularExpression exp3("SELECT (?<columns>.+) FROM (?<table>.+) WHERE (?<condition>.+)");

    QRegularExpressionMatch match;

    match = exp3.match(vql);
    if (match.hasMatch())
    {
        query.setColumns(match.captured("columns").split(","));
        query.setTable(match.captured("table"));
        query.setCondition(match.captured("condition"));
        return query;
    }

    match = exp2.match(vql);
    if (match.hasMatch())
    {
        query.setColumns(match.captured("columns").split(","));
        query.setTable(match.captured("table"));
        return query;

    }

    match = exp1.match(vql);
    if (match.hasMatch())
    {
        query.setColumns(match.captured("columns").split(","));
        return query;
    }
}


}
