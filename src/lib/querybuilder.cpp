#include "querybuilder.h"
namespace core {

QueryBuilder::QueryBuilder()
{

    mRegExps[SelectFrom]        = QRegularExpression("SELECT (?<select>.+) FROM (?<from>\\w+)$");
    mRegExps[SelectFromWhere]   = QRegularExpression("SELECT (?<select>.+) FROM (?<from>\\w+) WHERE (?<where>.+)$");
    mRegExps[SelectFromWhereIn] = QRegularExpression("SELECT (?<select>.+) FROM (?<from>\\w+) WHERE (?<where>.+) IN (?<in>\\w+)$");

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
    QString out;
    QStringList genotypeSamples = detectGenotypeField();

    qDebug()<<"ICI "<<genotypeSamples<<" "<<genotypeSamples.size();

    if (genotypeSamples.isEmpty())
    {
        qDebug()<<"CONDITION "<<condition()<<" "<<condition().size();
        if (condition().isEmpty()){
            out = QString("SELECT %1 FROM %2")
                    .arg(columns().join(","))
                    .arg(tableName());
        }

        else{
            out = QString("SELECT %1 FROM %2 WHERE %3")
                    .arg(columns().join(","))
                    .arg(tableName())
                    .arg(condition());
        }

    }
    else
    {
        QString joinsql;
        QStringList joinwheresql;

        for (QString sample : genotypeSamples)
        {
            joinsql.append(QStringLiteral(" LEFT JOIN genotypes as gt_%1 ON variants.id = gt_%1.variant_id ").arg(sample));
            joinwheresql.append(QStringLiteral(" gt_%1.sample_id = %2 ").arg(sample).arg(mSamplesIds[sample]));
        }

        if (!condition().isEmpty())
            joinwheresql.prepend(condition()+" ");

        out = QString("SELECT %1 FROM %2 %3 WHERE %4")
                .arg(columns().join(","))
                .arg(tableName())
                .arg(joinsql)
                .arg(joinwheresql.join(" AND "));
    }

    out += " LIMIT "+QString::number(limit());
    return out ;

}
//---------------------------------------------------------------------------------
bool QueryBuilder::hasGenotypeField() const
{
    return !detectGenotypeField().isEmpty();
}
//---------------------------------------------------------------------------------
void QueryBuilder::clear()
{
    mTableName.clear();
    mColumns.clear();
    mRegion.clear();
    mCondition.clear();
}

//---------------------------------------------------------------------------------

QString QueryBuilder::normGenotype(const QString &raw)
{
    // detect genotype[NAME].GT  => gt_NAME.GT
    QRegularExpression exp;
    QRegularExpressionMatchIterator all;

    exp.setPattern(QStringLiteral("genotype\\[(\'|\")?(?<sample>\\w+)(\'|\")?\\]\\.(?<param>\\w+)"));
    all = exp.globalMatch(raw);

    QString out = raw;
    while (all.hasNext())
    {
        QRegularExpressionMatch m = all.next();
        qDebug()<<m.capturedTexts();
        out = out.replace(m.captured(0), QString("gt_%1.%2").arg(m.captured("sample")).arg(m.captured("param")));
    }
    return out;
}
//---------------------------------------------------------------------------------

QString QueryBuilder::normAnnotation(const QString &raw)
{
    // detect INFO.DP or ANN.DP == > INFO_DP
    QRegularExpression exp;
    QRegularExpressionMatchIterator all;

    exp.setPattern("(?<key>\\w+)\\.(?<value>\\w+)");
    all = exp.globalMatch(raw);

    QString out = raw;
    while (all.hasNext())
    {
        QRegularExpressionMatch m = all.next();
        // Not not transform gt..
        if (!m.captured(0).contains("gt"))
            out = out.replace(m.captured(0), QString("%1_%2").arg(m.captured("key")).arg(m.captured("value")));
    }

    return out;
}
//---------------------------------------------------------------------------------

QStringList QueryBuilder::detectGenotypeField() const
{
    QStringList genotypeSamples;
    QSet<QString> uniques;
    // genotype fields can be in columns or conditions
    QString raw = columns().join(" ") + " " + condition();
    // detect gt_sacha_GT fields like
    QRegularExpression exp (QStringLiteral("gt_(?<sample>\\w+).(?<field>\\w+)"));
    QRegularExpressionMatchIterator all = exp.globalMatch(raw);

    while (all.hasNext())
    {
        QRegularExpressionMatch m = all.next();
        uniques.insert(m.captured(1));
    }

    for (QString s:  uniques)
        genotypeSamples.append(s);


    return genotypeSamples;
}
//---------------------------------------------------------------------------------

const QString &QueryBuilder::region() const
{
    return mRegion;
}
//---------------------------------------------------------------------------------

void QueryBuilder::setRegion(const QString &region)
{
    mRegion = region.simplified();
}
//---------------------------------------------------------------------------------

void QueryBuilder::setColumns(const QStringList &columns)
{
    mColumns.clear();
    for (QString s : columns)
    {
        if (!s.isEmpty())
            mColumns.append(s.simplified());
    }

}
//---------------------------------------------------------------------------------

void QueryBuilder::setTableName(const QString &tableName)
{
    mTableName = tableName.simplified();
}
//---------------------------------------------------------------------------------

void QueryBuilder::setCondition(const QString &condition)
{
    mCondition = condition.simplified();
}
//---------------------------------------------------------------------------------

void QueryBuilder::setOrderBy(const QString &order)
{
    mOrderBy = order;
}
//---------------------------------------------------------------------------------

void QueryBuilder::fromRawQuery(const QString& raw)
{
    mRaw = raw;
    QString processRaw = raw;

    QueryType type = queryMatch(processRaw);

    if (!type)
    {
        qDebug()<<"invalid query";
        return;
    }

    clear();

    processRaw = normGenotype(processRaw);
    processRaw = normAnnotation(processRaw);


    qDebug()<<processRaw;

    if (type == QueryType::SelectFrom)
    {
        QRegularExpressionMatch match = mRegExps[type].match(processRaw);
        setColumns(match.captured("select").replace(QChar::Space,',').split(","));
        setTableName(match.captured("from"));
    }


    if (type == QueryType::SelectFromWhere)
    {
        QRegularExpressionMatch match = mRegExps[type].match(processRaw);
        setColumns(match.captured("select").replace(QChar::Space,',').split(","));
        setTableName(match.captured("from"));
        setCondition(match.captured("where"));

    }

    if (type == QueryType::SelectFromWhereIn)
    {
        QRegularExpressionMatch match = mRegExps[type].match(processRaw);
        setColumns(match.captured("select").replace(QChar::Space,',').split(","));
        setTableName(match.captured("from"));
        setCondition(match.captured("where"));
        setRegion(match.captured("in"));
    }


    qInfo()<<"COLUMNS"<<columns();
    qInfo()<<"TABLE"<<tableName();
    qInfo()<<"CONDITION"<<condition();
    qInfo()<<"REGION"<<region();


}
//---------------------------------------------------------------------------------

QueryBuilder::QueryType QueryBuilder::queryMatch(const QString &raw)
{

    for (QueryType type : mRegExps.keys())
    {
        if (mRegExps[type].match(raw).hasMatch())
            return type;
    }

    return QueryBuilder::InValid;

}

//---------------------------------------------------------------------------------

void QueryBuilder::setSampleIds(const QHash<QString, int> &sampleIds)
{
    mSamplesIds = sampleIds;
}


//---------------------------------------------------------------------------------




}
