#ifndef VARIANTQUERY_H
#define VARIANTQUERY_H
#include <QtCore>
#include "project.h"
#include "region.h"

namespace cvar {

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

    bool isValid() const;


    QStringList columns() const;
    QStringList rawColumns() const;
    void setColumns(const QStringList &columns);

    QString table() const;
    QString rawTable() const;
    void setTable(const QString &table);

    QString condition() const;
    QString rawCondition() const;
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


    static VariantQuery fromVql(const QString& text);


    Qt::SortOrder sortOder() const;
    void setSortOrder(Qt::SortOrder sortOder);

    void setNoLimit();

    const QString &region() const;
    void setRegion(const QString& region);

protected:
    QStringList detectSamplesFields() const;
    void replaceSampleFields(QString& text, bool setAS = false) const;

private:
    QStringList mColumns;
    QString mTable = "variants";
    QStringList mOrderBy;
    QString mCondition;
    QStringList mGroupBy = {};
    int mOffset = 0;
    int mLimit  = 100;
    Qt::SortOrder mSortOder = Qt::AscendingOrder;
    QString mRegion;


};

}
#endif // VARIANTQUERY_H
