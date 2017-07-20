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
    enum QueryStruct
    {
        Columns,
        Columns_Where,
        Columns_Where_In,
        Unknown
    };

    QueryBuilder();
    QueryBuilder(const QString& tableName,
          const QStringList& columns,
          const QString& condition);
    QueryBuilder(const QString& raw);

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
    void parse(const QString& raw) ;

    QueryStruct queryStruct() const;

protected:
    // detect if columns or condition have the extra keyworks genotype().GT
    bool hasGenotypeInColumns();
    bool hasGenotypeInCondition();




private:
    QString mTableName;
    QStringList mColumns;
    QString mCondition;
    QString mRegion;
    QString mRaw;

    int mOffset = 0;
    int mLimit  = 100;

    const QString GenotypeKeyword = "genotype";
    const QString SampleKeyword = "sample";

    // sampleName : genotype Fields.
    // exemple : SACHA : GT
    QHash<QString, QString> mGenotypeFields;


};

}

#endif // VARIANTQUERY_H
