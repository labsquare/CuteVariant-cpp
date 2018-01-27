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
    //TODO check valid query


    return true;


}

const QStringList& VariantQuery::columns() const
{
    return mColumns;
}

//QStringList VariantQuery::rawColumns() const
//{
//    QStringList raw;

//    if (columns().join("") =="*")
//        return QStringList({QString("%1.*").arg(rawTable())});


//    for (QString col : columns())
//    {
//        col = col.remove("variants.");

//        // if col is a sample fields ...
//        if (col.contains("["))
//            replaceSampleFields(col, true);
//        else
//            col = QString("%1.`%2` as '%2' ").arg(rawTable(),col);


//        qDebug()<<col;

//        raw.append(col);
//    }
//    return raw;
//}


void VariantQuery::setColumns(const QStringList &columns)
{
    mColumns.clear();
    for (QString col: columns)
    {
        mColumns.append(col.simplified());
    }
}

QString VariantQuery::tableName() const
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

QString VariantQuery::toSql() const
{

    const SqliteManager *sql = cutevariant->sqliteManager();

    // the sql query to return
    QString s_query;

    // select statement
    QString s_select = "SELECT " + rawColumns().join(",");

    // where statement
    QString s_where = !rawCondition().isEmpty() ? " WHERE "+rawCondition() : QString();

    // from statement
    QString s_from = " FROM "+rawTableName();

    // left join statement
    QString s_leftJoin;

    // group by statement
    QString s_groupBy = rawGroupBy();

    // order by statement
    QString s_orderBy = rawOrderBy();

    // limt offset statement
    QString s_limitOffset = rawLimitOffset();

    // join variant with genotype : LEFT JOIN genotype as gt_<sample> ON variant.id = gt_<sample>.variant_id
    QStringList joinSamples;
    // specify genotype id : WHERE gt_<sample>.sample_id = 4
    QStringList whereSamples;


    // get samples Ids
    QHash<QString, int> samplesIds;
    for (const Sample& s : sql->samples()){
        samplesIds[s.name()] = s.id();
    }

    // Create sample join relation
    for (QString sample : extractSamples())
    {
        joinSamples.append(QString(" LEFT JOIN genotypes as `gt_%1` ON %2.id = `gt_%1`.variant_id ").arg(sample).arg(tableName()));
        whereSamples.append(QString(" `gt_%1`.sample_id = %2 ").arg(sample).arg(samplesIds[sample]));
    }

    if (!joinSamples.isEmpty())
    {
        s_leftJoin = joinSamples.join(" ");

        if (s_where.isEmpty())
            s_where = "WHERE "+whereSamples.join(" AND ");
        else
            s_where.append(" AND "+whereSamples.join(" AND "));
    }


    // add extra fields for group by
    if (!groupBy().isEmpty())
        s_select += QString(" ,COUNT(%1.id) as 'count', group_concat(%1.id) as 'childs' ").arg(tableName());

    // add region
    if (!bed().isEmpty())
        s_from += ",regions";

    // Create query

    qDebug()<<"select:"<<s_select;
    qDebug()<<"from:"<<s_from;
    qDebug()<<"leftJoin:"<<s_leftJoin;
    qDebug()<<"where:"<<s_where;
    qDebug()<<"groupBy:"<<s_groupBy;
    qDebug()<<"orderBy:"<<s_orderBy;
    qDebug()<<"limitOffset:"<<s_limitOffset;


    s_query = s_select + s_from + s_leftJoin + s_where + s_groupBy + s_orderBy + s_limitOffset;






    //    // SELECT columns FROM table LEFT JOIN ON ..
    //    if (!joinSamples.isEmpty())
    //        query.append(joinSamples.join(" "));

    //    // SELECT columns FROM table WHERE conditions
    //    if (!where.isEmpty())
    //        query.append(QString(" WHERE %1 ").arg(where));


    //    // check region
    //    // TODO check if region exists
    //    if (!mBed.isEmpty())
    //    {
    //        if (where.isEmpty())
    //            query.append(QString(" WHERE %1.pos BETWEEN regions.start AND regions.end AND %1.chr = regions.chr").arg(tableName));
    //        else
    //            query.append(QString(" AND %1.pos BETWEEN regions.start AND regions.end AND %1.chr = regions.chr").arg(tableName));
    //    }



    //    // SELECT columns FROM table WHERE condition GROUP BY
    //    // TODO ugly
    //    QStringList gp = groupBy();
    //    for (QString& i : gp )
    //        i.prepend(tableName+".");

    //    if (!groupBy().isEmpty())
    //        query.append(QString(" GROUP BY %1 ").arg(gp.join(",")));

    //    if (!orderBy().isEmpty())
    //        query.append(QString( " ORDER BY %1 %2 ").arg(orderBy().join(",")).arg(mSortOder==Qt::AscendingOrder ? "ASC" : "DESC"));

    //    // LIMIT and OFFSET
    //    if (limit() > 0)
    //        query.append(QString(" LIMIT %1 OFFSET %2").arg(limit()).arg(offset()));

    return s_query.simplified();
}

QStringList VariantQuery::extractSamples() const
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

QString VariantQuery::replaceSampleFields(const QString &text, bool label) const
{
    //rename genotype fields
    // ex : sample["CGH1077"].DP   === >  gt_CGH1077`.DP as 'CGH1077.DP'

    QRegularExpression re("sample\\[\\\"(?<sample>[^\\s]+)\\\"\\]\\.(?<arg>[^\\s]+)");
    QRegularExpressionMatchIterator it = re.globalMatch(text);

    QString tmp = text;

    while (it.hasNext())
    {
        QRegularExpressionMatch match = it.next();
        if (label)
            tmp.replace(match.captured(), QString("`gt_%1`.%2 as '%1.%2'").arg(match.captured("sample"), match.captured("arg")));
        else
            tmp.replace(match.captured(), QString("`gt_%1`.%2").arg(match.captured("sample"), match.captured("arg")));


    }

    return tmp;
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

const QString &VariantQuery::bed() const
{
    return mBed;
}

void VariantQuery::setBed(const QString &region)
{
    mBed = region;
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
    VqlParser parser;

    if (parser.parse(text.simplified().toStdString()))
    {
        // set table name
        query.setTable(QString::fromStdString(parser.tableName()));

        // set columns
        QStringList columnsTmp;

        qDebug()<<"parser columns "<<parser.columns().size();

        for (std::string col : parser.columns())
            columnsTmp.append(QString::fromStdString(col));
        query.setColumns(columnsTmp);

        // set condition
        query.setCondition(QString::fromStdString(parser.conditions()));

        // set inside
        query.setBed(QString::fromStdString(parser.region()));

    }

    return query;

}



//===== PROTECTED

const QStringList VariantQuery::rawColumns() const
{
    QStringList raw;

    raw.append(QString("%1.id AS id").arg(rawTableName()));

    for (QString col : columns())
    {
        col = col.remove("variants.");

        // if col is a sample fields ...
        if (col.contains("sample["))
            col = replaceSampleFields(col,true);
        else
        {
            col = col.replace(".","_");
            col = QString("%1.`%2` as '%2' ").arg(rawTableName(),col);
        }

        raw.append(col);
    }

    return raw;
}

const QString VariantQuery::rawTableName() const
{
    if (tableName().isEmpty())
        return "'variants'";
    else
        return QString("`%1`").arg(tableName());
}

const QString VariantQuery::rawCondition() const
{
    if (condition().isEmpty())
        return QString();
    else
        return replaceSampleFields(condition(), false);
}

const QString VariantQuery::rawOrderBy() const
{
    if (orderBy().isEmpty())
        return QString();
    else
        return QString( " ORDER BY %1 %2 ").arg(orderBy().join(",")).arg(mSortOder==Qt::AscendingOrder ? "ASC" : "DESC");
}

const QString VariantQuery::rawGroupBy() const
{
    QStringList gp = groupBy();
    for (QString& i : gp )
        i.prepend(rawTableName()+".");

    if (!groupBy().isEmpty())
        return QString(" GROUP BY %1 ").arg(gp.join(","));
    else
        return QString();
}

const QString VariantQuery::rawLimitOffset() const
{
    if (limit() == 0)
        return QString();

    return QString(" LIMIT %1 OFFSET %2").arg(limit()).arg(offset());

}


QDebug operator<< (QDebug d, const VariantQuery &query)
{
    d<<"\n";
    d<<"table\t"<<query.tableName()<<"\n";
    d<<"columns size\t"<<query.columns().size()<<"\n";
    d<<"columns\t"<<query.columns()<<"\n";
    d<<"condition\t"<<query.condition()<<"\n";
    d<<"bed\t"<<query.bed()<<"\n";
    d<<"group by\t"<<query.groupBy()<<"\n";
    d<<"order by\t"<<query.orderBy()<<"\n";
    d<<"offset \t"<<query.offset()<<"\n";
    d<<"limit \t"<<query.limit()<<"\n";

    return d;
}



}
