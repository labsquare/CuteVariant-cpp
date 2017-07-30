#ifndef VARIANTQUERY_H
#define VARIANTQUERY_H
#include <QtCore>
#include "project.h"

namespace core {

class SqliteManager;
class VariantQuery
{
public:
    VariantQuery();
    VariantQuery(const QStringList& columns,
                 const QString& table);

    VariantQuery(const QStringList& columns,
                 const QString& table,
                 const QString& conditions);


    QStringList columns() const;
    void setColumns(const QStringList &columns);

    QString table() const;
    void setTable(const QString &table);

    QString condition() const;
    void setCondition(const QString &condition);

    int offset() const;
    void setOffset(int offset);

    int limit() const;
    void setLimit(int limit);

    QStringList groupBy() const;
    void setGroupBy(const QStringList &groupBy);

    QString toSql(const SqliteManager * sql) const;

    QStringList orderBy() const;
    void setOrderBy(const QStringList &orderBy);


    Qt::SortOrder sortOder() const;
    void setSortOder(Qt::SortOrder sortOder);

protected:
    QStringList detectSamplesFields() const;

private:
    QStringList mColumns;
    QString mTable = "variants";
    QStringList mOrderBy;
    QString mCondition;
    QStringList mGroupBy = {};
    int mOffset = 0;
    int mLimit  = 100;
    Qt::SortOrder mSortOder = Qt::AscendingOrder;


};

}
#endif // VARIANTQUERY_H
