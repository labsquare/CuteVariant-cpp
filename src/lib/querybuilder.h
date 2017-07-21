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
    QueryBuilder(const QString& raw);


    const QStringList &columns() const;
    const QString& tableName() const;
    const QString& condition() const;
    const QString& region() const;
    int offset() const;
    int limit() const;
    const QString& orderBy() const;
    QueryStruct queryStruct() const;


    void setRegion(const QString& region);
    void setColumns(const QStringList& columns);
    void setTableName(const QString& tableName);
    void setCondition(const QString& condition);
    void setOrderBy(const QString& order);

    void setSampleIds(const QHash<QString, int>& sampleIds);



    void setRawQuery(const QString& raw);
    QString toSql() const;


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
    QString mOrderBy = "ANN_GENE_NAME";

    const QString GenotypeKeyword = "genotype";
    const QString SampleKeyword = "sample";

    // sampleName : genotype Fields.
    // exemple : SACHA : GT
    QHash<QString, QString> mGenotypeFields;

    // store samples and ids
    QHash<QString, int> mSamplesIds;






};

}

#endif // VARIANTQUERY_H
