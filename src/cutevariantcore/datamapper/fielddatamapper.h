#ifndef FIELDDATAMAPPER_H
#define FIELDDATAMAPPER_H
#include "datamapper.h"
#include "field.h"
namespace cvar {
class FieldDataMapper : public DataMapper<Field, FieldDataMapper>
{
public:
    FieldDataMapper();


    virtual QHash<QString, QVariant> toSql(const Field& record) const override ;
    virtual Field fromSql(const QSqlRecord& record) const override;


};
}
#endif // FIELDDATAMAPPER_H
