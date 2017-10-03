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

QStringList VariantQuery::rawColumns() const
{
    QStringList raw;

    if (columns().join("") =="*")
        return QStringList({QString("%1.*").arg(rawTable())});


    for (QString col : columns())
    {
        col = col.remove("variants.");

        // if col is a sample fields ...
        if (col.contains("["))
            replaceSampleFields(col, true);
        else
            col = QString("%1.`%2` as '%2' ").arg(rawTable(),col);


        qDebug()<<col;

        raw.append(col);
    }
    return raw;
}


void VariantQuery::setColumns(const QStringList &columns)
{
    mColumns.clear();
    for (QString col: columns)
    {
        mColumns.append(col.simplified());
    }
}

QString VariantQuery::table() const
{
    return mTable;
}

QString VariantQuery::rawTable() const
{
    if (table().isEmpty())
        return QString();

    return QString("`%1`").arg(table());
}

void VariantQuery::setTable(const QString &table)
{
    mTable = table;
}

QString VariantQuery::condition() const
{
    return mCondition;
}

QString VariantQuery::rawCondition() const
{
    // HUGE HACK... VERRRRRY UGLY
    QString raw = condition();

    for (QString t : raw.split("sample"))
    {
        QString a = t;
        replaceSampleFields(a);
    }

    replaceSampleFields(raw);
    return raw;
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

    QString select     = table()+".id as id, "+rawColumns().join(",");
    QString tableName  = rawTable().isEmpty() ? "variants" : rawTable();
    QString where      = rawCondition();

    QStringList joinSamples;
    QStringList whereSamples;


    // get samples Ids
    QHash<QString, int> samplesIds;
    for (Sample s : sql->samples()){
        samplesIds[s.name()] = s.id();
    }

    // Create join
    qDebug()<<"DETECT SAMPLES "<<detectSamplesFields();

    for (QString sample : detectSamplesFields())
    {
        joinSamples.append(QString(" LEFT JOIN genotypes as `gt_%1` ON %2.id = `gt_%1`.variant_id ").arg(sample).arg(tableName));
        whereSamples.append(QString(" `gt_%1`.sample_id = %2 ").arg(sample).arg(samplesIds[sample]));
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
        select += QString(" ,COUNT(%1.id) as 'count', group_concat(%1.id) as 'childs' ").arg(tableName);


    // SELECT columns FROM table
    if (region().isEmpty())
        query = QString("SELECT %1 FROM %2").arg(select).arg(tableName);
    else
        query = QString("SELECT %1 FROM %2, regions").arg(select).arg(tableName);


    // SELECT columns FROM table LEFT JOIN ON ..
    if (!joinSamples.isEmpty())
        query.append(joinSamples.join(" "));

    // SELECT columns FROM table WHERE conditions
    if (!where.isEmpty())
        query.append(QString(" WHERE %1 ").arg(where));


    // check region
    // TODO check if region exists
    if (!mRegion.isEmpty())
    {
        if (where.isEmpty())
            query.append(QString(" WHERE %1.pos BETWEEN regions.start AND regions.end AND %1.chr = regions.chr").arg(tableName));
        else
            query.append(QString(" AND %1.pos BETWEEN regions.start AND regions.end AND %1.chr = regions.chr").arg(tableName));
    }



    // SELECT columns FROM table WHERE condition GROUP BY
    // TODO ugly
    QStringList gp = groupBy();
    for (QString& i : gp )
        i.prepend(tableName+".");

    if (!groupBy().isEmpty())
        query.append(QString(" GROUP BY %1 ").arg(gp.join(",")));

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
    QRegularExpression re("sample\\[(?<sample>[^.]+)\\]");
    QString source = columns().join(" ") +" "+ condition();

    QRegularExpressionMatchIterator it = re.globalMatch(source);
    while(it.hasNext())
    {
        QRegularExpressionMatch match = it.next();
        sampleName.insert(match.captured("sample").remove("\""));
    }

    return sampleName.toList();
}

void VariantQuery::replaceSampleFields(QString &text, bool setAS) const
{
    // rename genotype fields
    QRegularExpression re("sample\\[\\\"(?<sample>[^\\s]+)\\\"\\]\\.(?<arg>[^\\s]+)");
    QRegularExpressionMatchIterator it = re.globalMatch(text);

    while (it.hasNext())
    {
        QRegularExpressionMatch match = it.next();
        if (setAS)
            text.replace(match.captured(), QString("`gt_%1`.%2 as '%1.%2'").arg(match.captured("sample"), match.captured("arg")));
        else
            text.replace(match.captured(), QString("`gt_%1`.%2").arg(match.captured("sample"), match.captured("arg")));
    }

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

const QString &VariantQuery::region() const
{
    return mRegion;
}

void VariantQuery::setRegion(const QString &region)
{
    mRegion = region;
}

QStringList VariantQuery::orderBy() const
{
    return mOrderBy;
}

void VariantQuery::setOrderBy(const QStringList &orderBy)
{
    mOrderBy = orderBy;
}

VariantQuery VariantQuery::fromVql(const QString &text)
{
    VariantQuery query;
    QString vql = text.simplified();

    QRegularExpression exp1("SELECT (?<columns>.+)");
    QRegularExpression exp2("SELECT (?<columns>.+) FROM (?<table>.+)");
    QRegularExpression exp3("SELECT (?<columns>.+) FROM (?<table>.+) WHERE (?<condition>.+)");
    QRegularExpression exp4("SELECT (?<columns>.+) FROM (?<table>.+) REGION (?<region>.+)");

    QRegularExpressionMatch match;

    match = exp4.match(vql);
    if (match.hasMatch())
    {

        query.setColumns(match.captured("columns").simplified().split(","));
        query.setTable(match.captured("table"));
        //        query.setCondition(match.captured("condition"));
        query.setRegion(match.captured("region"));
        return query;
    }


    match = exp3.match(vql);
    if (match.hasMatch())
    {
        query.setColumns(match.captured("columns").simplified().split(","));
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
