#ifndef VARIANTQUERY_H
#define VARIANTQUERY_H
#include <QtCore>
#include "field.h"
#include "sqlitemanager.h"

namespace core {
/*!
 * \brief The VariantQuery class
 * Use this class to generate sqlite query
 */
class SqliteManager;
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

    QueryBuilder(SqliteManager * sqlite);


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
    void setFromRaw(const QString& raw);
    void setLimit(int limit);
    void setOffset(int offset);

    QueryType queryMatch(const QString& raw);

    QString toSql() const;

    bool hasGenotypeField() const;


    void clear();

protected:


    QString normGenotype(const QString& raw);
    QString normAnnotation(const QString& raw);
    QStringList detectGenotypeField() const ;



private:
    QString mTableName;
    QStringList mColumns;
    QString mCondition;
    QString mRegion;
    int mOffset      = 0;
    int mLimit       = 100;
    QString mOrderBy = "ID";
    QString mRaw;
    QHash<QueryType, QRegularExpression> mRegExps;

    SqliteManager * mSqlite;



};

}

#endif // VARIANTQUERY_H
