#ifndef VARIANTQUERY_H
#define VARIANTQUERY_H
#include <QtCore>
#include "field.h"

namespace core {
/*!
 * \brief The VariantQuery class
 * Use this class to generate sqlite query
 */
class QueryBuilder
{
public:
    enum QueryType
    {
        InValid,
        SelectFrom,
        SelectFromWhere,
        SelectFromWhereIn,
    };

    QueryBuilder();


    const QStringList &columns() const;
    const QString& tableName() const;
    const QString& condition() const;
    const QString& region() const;
    int offset() const;
    int limit() const;
    const QString& orderBy() const;



    void setRegion(const QString& region);
    void setColumns(const QStringList& columns);
    void setTableName(const QString& tableName);
    void setCondition(const QString& condition);
    void setOrderBy(const QString& order);
    void setSampleIds(const QHash<QString, int>& sampleIds);
    void setRawQuery(const QString& raw);

    QueryType queryMatch(const QString& raw);

    QString toSql() const;


protected:




private:
    QString mTableName;
    QStringList mColumns;
    QString mCondition;
    QString mRegion;
    QString mRaw;
    int mOffset      = 0;
    int mLimit       = 100;
    QString mOrderBy = "ID";


    QHash<QueryType, QRegularExpression> mRegExps;


    // store samples and ids
    QHash<QString, int> mSamplesIds;






};

}

#endif // VARIANTQUERY_H
