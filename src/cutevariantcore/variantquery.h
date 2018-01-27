#ifndef VARIANTQUERY_H
#define VARIANTQUERY_H
#include <QtCore>
#include "project.h"
#include "region.h"

#include "vqlparser.h"


namespace cvar {

class SqliteManager;
class VariantQuery
{
public:
    VariantQuery();
    VariantQuery(const QStringList& columns,
                 const QString& tableName);

    VariantQuery(const QStringList& columns,
                 const QString& tableName,
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
    const QString& tableName() const;

    /*!
     * \brief setTable
     * \param tableName
     */
    void setTable(const QString &tableName);

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
    const QString &bed() const;
    /*!
     * \brief setBed
     * \param bed
     */
    void setBed(const QString& bed);

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

    /*!
     * \brief fromVql create a VariantQuery from vql statement
     * \param text
     * \return
     */
    static VariantQuery fromVql(const QString& text);


    Qt::SortOrder sortOder() const;
    void setSortOrder(Qt::SortOrder sortOder);

    void setNoLimit();

protected:

     const QStringList rawColumns() const;
     const QString rawTableName() const;
     const QString rawCondition() const;
     const QString rawOrderBy() const;
     const QString rawGroupBy() const;
     const QString rawLimitOffset() const;
     const QString rawBed() const;


    QStringList extractSamples() const;
    QString replaceSampleFields(const QString& text, bool label = false) const;

private:
    QStringList mColumns;
    QString mTable = "variants";
    QString mCondition;
    QString mBed;
    QStringList mGroupBy = {};
    QStringList mOrderBy;
    int mOffset = 0;
    int mLimit  = 100;
    Qt::SortOrder mSortOder = Qt::AscendingOrder;


};


QDebug operator<< (QDebug d, const VariantQuery &query);

}
#endif // VARIANTQUERY_H
