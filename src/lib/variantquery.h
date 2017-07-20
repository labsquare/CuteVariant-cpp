#ifndef VARIANTQUERY_H
#define VARIANTQUERY_H
#include <QtCore>
#include "field.h"

namespace core {
/*!
 * \brief The VariantQuery class
 * Use this class to generate sqlite query
 */
class VariantQuery
{
public:
    enum QueryStruct
    {
        Columns,
        Columns_Where,
        Columns_Where_In,
        Unknown
    };

    VariantQuery(const QString& tableName = "variants",
                 const QStringList& columns = QStringList(),
                 const QString& condition = QString());

    const QStringList &columns() const;
    const QString& tableName() const;
    const QString& condition() const;
    const QString& region() const;
    int offset() const;
    int limit() const;
    void setRegion(const QString& region);
    void setColumns(const QStringList& columns);
    void setTableName(const QString& tableName);
    void setCondition(const QString& condition);

    QString toSql() const;
    static VariantQuery fromString(const QString& raw) ;

    QueryStruct queryStruct() const;



private:
    QString mTableName;
    QStringList mColumns;
    QString mCondition;
    QString mRegion;

    int mOffset = 0;
    int mLimit  = 100;


};

}

#endif // VARIANTQUERY_H
