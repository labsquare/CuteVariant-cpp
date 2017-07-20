#include "variantquery.h"
namespace core {

VariantQuery::VariantQuery(const QString& tableName, const QStringList &columns, const QString &condtion)
    :mTableName(tableName), mColumns(columns), mCondition(condtion)
{

}

const QStringList &VariantQuery::columns() const
{
    return mColumns;
}

const QString &VariantQuery::condition() const
{
    return mCondition;
}

const QString &VariantQuery::tableName() const
{
    return mTableName;
}

int VariantQuery::offset() const
{
    return mOffset;
}

int VariantQuery::limit() const
{
    return mLimit;
}

QString VariantQuery::toSql() const
{

  if (queryStruct() == Unknown)
      return "Unknown";

  if (queryStruct() == Columns)
  {
   QString query = QString("SELECT chr,pos,ref,alt, %1 FROM %2 LIMIT %3 OFFSET %4")
           .arg(columns().join(','))
           .arg(tableName())
           .arg(limit())
           .arg(offset());

    return query;
  }


  if (queryStruct() == Columns_Where)
  {
   QString query = QString("SELECT chr,pos,ref,alt, %1 FROM %2 WHERE %3 LIMIT %4 OFFSET %5")
           .arg(columns().join(','))
           .arg(tableName())
           .arg(condition())
           .arg(limit())
           .arg(offset());

    return query;
  }


}

const QString &VariantQuery::region() const
{
    return mRegion;
}

void VariantQuery::setRegion(const QString &region)
{
    mRegion = region;
}

void VariantQuery::setColumns(const QStringList &columns)
{
    mColumns = columns;
}

void VariantQuery::setTableName(const QString &tableName)
{
    mTableName = tableName;
}

void VariantQuery::setCondition(const QString &condition)
{
    mCondition = condition;
}

VariantQuery VariantQuery::fromString(const QString& raw)
{
    VariantQuery q;

    QRegularExpression exp1(QStringLiteral("^SELECT (?<columns>.+) FROM (?<table>\\w+)$"));
    QRegularExpression exp2(QStringLiteral("^SELECT (?<columns>.+) FROM (?<table>\\w+) WHERE (?<condition>.+)$"));
    QRegularExpression exp3(QStringLiteral("^SELECT (?<columns>.+) FROM (?<table>\\w+) WHERE (?<condition>.+) IN (?<region>\\w+)$"));

    QRegularExpressionMatch match;

    // SELECT x FROM y WHERE z IN r
    match = exp3.match(raw);
    if (match.hasMatch())
    {
        qDebug()<<"exp3"<<match.capturedTexts();
        q.setColumns(match.captured("columns").split(","));
        q.setTableName(match.captured("table"));
        q.setCondition(match.captured("condition"));
        q.setRegion(match.captured("region"));
        return q;
    }

    // SELECT x FROM y WHERE z
    match = exp2.match(raw);
    if (match.hasMatch())
    {
        qDebug()<<"exp2"<<match.capturedTexts();
        q.setColumns(match.captured("columns").split(","));
        q.setTableName(match.captured("table"));
        q.setCondition(match.captured("condition"));
        return q;
    }

    // SELECT x FROM y
    match = exp1.match(raw);
    if (match.hasMatch())
    {

        qDebug()<<"exp1"<<match.capturedTexts();
        q.setColumns(match.captured("columns").split(","));
        q.setTableName(match.captured("table"));
        return q;
    }

    return q;
}

VariantQuery::QueryStruct VariantQuery::queryStruct() const
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




}
