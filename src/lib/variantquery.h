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
    VariantQuery(const QString& tableName = "variants", const QStringList& columns = QStringList(), const QJsonObject& filter = QJsonObject(), int offset = 0, int limit = 1000);
    const QStringList& columns() const;
    int offset() const;
    int limit() const;
    QString toSql() const;

    static VariantQuery fromString() ;

private:
    QString mTableName;
    QStringList mColumns;
    QJsonObject mFilter;
    int mOffset = 0;
    int mLimit  = 0;


};

}

#endif // VARIANTQUERY_H
