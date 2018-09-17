#ifndef VARIANTQUERY_H
#define VARIANTQUERY_H
#include <QtCore>
#include "cutevariant.h"
#include "region.h"

#include "vqlparser.h"


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


    /*!
     * \brief isValid
     * \return true is query is valid
     */
    bool isValid() const;

    /*!
     * \brief columns
     * \return return columns selected
     */
    const QStringList& columns() const;

    /*!
     * \brief setColumns
     * \param columns
     */
    void setColumns(const QStringList &columns);

    /*!
     * \brief table
     * \return table name
     */
    const QString& table() const;

    /*!
     * \brief setTable
     * \param tableName
     */
    void setTable(const QString &table);

    /*!
     * \brief condition
     * \return where condition
     */
    const QString& condition() const;

    /*!
     * \brief setCondition
     * \param condition
     */
    void setCondition(const QString &condition);

    /*!
     * \brief bed
     * \return bed name
     */
    const QString &region() const;
    /*!
     * \brief setBed
     * \param bed
     */
    void setRegion(const QString& region);

    int offset() const;
    void setOffset(int offset);

    int limit() const;
    void setLimit(int limit);

    QStringList groupBy() const;
    void setGroupBy(const QStringList &groupBy);


    QStringList orderBy() const;
    void setOrderBy(const QStringList &orderBy);

    /*!
     * \brief toSql
     * \return raw sql statement
     */
    QString toSql() const;
    //QString toVql() const;
    /*!
     * \brief fromVql create a VariantQuery from vql statement
     * \param text
     * \return
     */
   // static VariantQuery fromVql(const QString& text);



    Qt::SortOrder sortOder() const;
    void setSortOrder(Qt::SortOrder sortOder);

    void setNoLimit();

protected:
     const QStringList sqlColumns() const;
     const QString sqlTableName() const;
     const QString sqlCondition() const;
     const QString sqlOrderBy() const;
     const QString sqlGroupBy() const;
     const QString sqlLimitOffset() const;
     const QString sqlRegion() const;


private:
    QStringList mColumns;
    QString mTable = "variants";
    QString mCondition;
    QString mRegion;
    QStringList mGroupBy = {};
    QStringList mOrderBy;
    int mOffset = 0;
    int mLimit  = 100;
    Qt::SortOrder mSortOder = Qt::AscendingOrder;

};


QDebug operator<< (QDebug d, const VariantQuery &query);

}
#endif // VARIANTQUERY_H
