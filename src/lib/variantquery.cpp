#include "variantquery.h"
namespace core {

VariantQuery::VariantQuery(const QString& tableName, const QStringList &columns, const QJsonObject &filter, int offset, int limit)
    :mTableName(tableName), mColumns(columns), mFilter(filter), mOffset(offset), mLimit(limit)
{

}

const QStringList &VariantQuery::columns() const
{
    return mColumns;
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

    QString query;
    if (mTableName == "variants")
    {

        query = QString("SELECT chr, pos, ref, alt FROM variants");


    }


    return query;


}

VariantQuery VariantQuery::fromString()
{
    VariantQuery q;



    return q;
}




}
