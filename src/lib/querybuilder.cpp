#include "querybuilder.h"
namespace core {

QueryBuilder::QueryBuilder()
{

}

//---------------------------------------------------------------------------------

QueryBuilder::QueryBuilder(const QString &raw)
{
    setRawQuery(raw);
}
//---------------------------------------------------------------------------------

const QStringList &QueryBuilder::columns() const
{
    return mColumns;
}
//---------------------------------------------------------------------------------

const QString &QueryBuilder::condition() const
{
    return mCondition;
}
//---------------------------------------------------------------------------------

const QString &QueryBuilder::tableName() const
{
    return mTableName;
}
//---------------------------------------------------------------------------------

int QueryBuilder::offset() const
{
    return mOffset;
}
//---------------------------------------------------------------------------------

int QueryBuilder::limit() const
{
    return mLimit;
}

const QString &QueryBuilder::orderBy() const
{
    return mOrderBy;
}
//---------------------------------------------------------------------------------

QString QueryBuilder::toSql() const
{


    if (queryStruct() == Unknown)
        return "Unknown";

    // build jointure with genotypes
    QStringList jointure;
    QString joinCond;

    if (!mGenotypeFields.isEmpty())
    {

        QStringList joinCondList;

        for (QString sample : mGenotypeFields.keys())
        {
            jointure.append(QString("LEFT JOIN genotypes AS g_%1 ON variants.id = g_%1.variant_id")
                            .arg(sample));

            joinCondList.append(QString("g_%1.sample_id == INDEX_OF_%1 ").arg(sample));

        }

        joinCond = "WHERE " + joinCondList.join(" AND ");

    }

    if (queryStruct() == Columns)
    {

        QString query = QString("SELECT chr,pos,ref,alt, %1 FROM %2 %5 %6  ORDER BY %7 LIMIT %3 OFFSET %4")
                .arg(columns().join(','))
                .arg(tableName())
                .arg(limit())
                .arg(offset())
                .arg(jointure.join(" "))
                .arg(joinCond)
                .arg(orderBy());

        return query;
    }


    if (queryStruct() == Columns_Where)
    {
        QString query = QString("SELECT chr,pos,ref,alt, %1 FROM %2 WHERE %3 ORDER BY %6 LIMIT %4 OFFSET %5")
                .arg(columns().join(','))
                .arg(tableName())
                .arg(condition())
                .arg(limit())
                .arg(offset())
                .arg(orderBy());

        return query;
    }


}
//---------------------------------------------------------------------------------

const QString &QueryBuilder::region() const
{
    return mRegion;
}
//---------------------------------------------------------------------------------

void QueryBuilder::setRegion(const QString &region)
{
    mRegion = region;
}
//---------------------------------------------------------------------------------

void QueryBuilder::setColumns(const QStringList &columns)
{
    mColumns = columns;
}
//---------------------------------------------------------------------------------

void QueryBuilder::setTableName(const QString &tableName)
{
    mTableName = tableName;
}
//---------------------------------------------------------------------------------

void QueryBuilder::setCondition(const QString &condition)
{
    mCondition = condition;
}
//---------------------------------------------------------------------------------

void QueryBuilder::setOrderBy(const QString &order)
{
    mOrderBy = order;
}
//---------------------------------------------------------------------------------

void QueryBuilder::setRawQuery(const QString& raw)
{
    mRaw = raw;
    QString processRaw = raw;

    // detect extra keywords
    // genotype columns
    mGenotypeFields.clear();
    QRegularExpression genotypeExp(QStringLiteral("genotype\\((?<sample>\\w+)\\)\\.(?<field>\\w+)"));
    QRegularExpressionMatchIterator all_match = genotypeExp.globalMatch(processRaw);
    while(all_match.hasNext())
    {

        QRegularExpressionMatch match = all_match.next();
        QString sample = match.captured("sample");
        QString field  = match.captured("field");
        qDebug()<<sample<<" "<<field;
        mGenotypeFields[sample] = field;
        processRaw = processRaw.replace(QRegularExpression(QString("genotype\\(%1\\)").arg(sample)),
                                        QString("g_%1").arg(sample.simplified()));


    }


    qDebug()<<"PROCESSSS" <<processRaw;

    // (?i) Mean ignore case
    QRegularExpression exp1(QStringLiteral("^(?i)(SELECT) (?<columns>.+) (?i)(FROM) (?<table>\\w+)$"));
    QRegularExpression exp2(QStringLiteral("^(?i)(SELECT) (?<columns>.+) (?i)(FROM) (?<table>\\w+) (?i)(WHERE) (?<condition>.+)$"));
    QRegularExpression exp3(QStringLiteral("^(?i)(SELECT) (?<columns>.+) (?i)(FROM) (?<table>\\w+) (?i)(WHERE) (?<condition>.+) IN (?<region>\\w+)$"));

    QRegularExpressionMatch match;

    // SELECT x FROM y WHERE z IN r
    match = exp3.match(processRaw);
    if (match.hasMatch())
    {
        qDebug()<<"exp3"<<match.capturedTexts();
        setColumns(match.captured("columns").split(","));
        setTableName(match.captured("table"));
        setCondition(match.captured("condition"));
        setRegion(match.captured("region"));

    }

    // SELECT x FROM y WHERE z
    match = exp2.match(processRaw);
    if (match.hasMatch())
    {
        qDebug()<<"exp2"<<match.capturedTexts();
        setColumns(match.captured("columns").split(","));
        setTableName(match.captured("table"));
        setCondition(match.captured("condition"));
    }

    // SELECT x FROM y
    match = exp1.match(processRaw);
    if (match.hasMatch())
    {

        qDebug()<<"exp1"<<match.capturedTexts();
        setColumns(match.captured("columns").split(","));
        setTableName(match.captured("table"));
    }

}
//---------------------------------------------------------------------------------
void QueryBuilder::setSampleId(const QString &name, int id)
{



    mSamplesIds.insert(name, id);
}
//---------------------------------------------------------------------------------

QueryBuilder::QueryStruct QueryBuilder::queryStruct() const
{
    if (columns().isEmpty())
        return Unknown;

    if (!columns().isEmpty() && condition().isEmpty() && region().isEmpty())
        return Columns;

    if (!columns().isEmpty() && !condition().isEmpty() && region().isEmpty())
        return Columns_Where;

    if (!columns().isEmpty() && !condition().isEmpty() && !region().isEmpty())
        return Columns_Where_In;


}
//---------------------------------------------------------------------------------
bool QueryBuilder::hasGenotypeInColumns()
{
    for (QString c : columns())
    {
        if (c.contains(GenotypeKeyword))
            return true;
    }
    return false;
}
//---------------------------------------------------------------------------------

bool QueryBuilder::hasGenotypeInCondition()
{
    return condition().contains(GenotypeKeyword);
}
//---------------------------------------------------------------------------------






}
