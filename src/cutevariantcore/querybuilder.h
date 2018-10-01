#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
#include <QtCore>
#include "view.h"
namespace cvar {

class QueryBuilder
{
public:
    QueryBuilder(const QStringList& columns  = {"rowid"},
                 const QString& table  = "variants",
                 const QString& condition = QString());

    QString toSql() const;


    void addColumn(const QString& col);
    void addSortColumns(const QString& col, Qt::SortOrder order);

    QStringList columns() const;
    void setColumns(const QStringList &columns);
    void clearSortColumns();

    QString table() const;
    void setTable(const QString &table);

    QString condition() const;
    void setCondition(const QString &condition);

    Qt::SortOrder order() const;
    void setOrder(Qt::SortOrder order);

    QString groupBy() const;
    void setGroupBy(const QString &groupBy);

    View createView(const QString& name, const QString & description) const;

    int limit() const;
    void setLimit(int limit);

    int offset() const;
    void setOffset(int offset);

protected:
    static QString quote(const QString& word);
    static QStringList quote(const QStringList& words);


private:
    QStringList mColumns;
    QString mTable;
    QString mCondition;

    QList<QPair<QString, Qt::SortOrder>> mColumnsOrder;

    QString mGroupBy;

    int mCountCache = 0;
    int mLimit  = 0;
    int mOffset = 0;

};

}

#endif // QUERYBUILDER_H
