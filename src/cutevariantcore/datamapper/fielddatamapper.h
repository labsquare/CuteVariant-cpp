#ifndef FIELDDATAMAPPER_H
#define FIELDDATAMAPPER_H
#include "datamapper.h"
#include "field.h"
namespace cvar {
class FieldDataMapper : public DataMapper<Field, FieldDataMapper>
{
public:
    FieldDataMapper();

    virtual bool insert(const QList<Field>& records) const override;
    virtual bool update(const Field& record) const override;
    virtual bool remove(const Field& record) const override;
    virtual bool createTable() const override;
    virtual Field get(int id) const override;
    virtual QList<Field> list(quint64 limit = 0, quint64 offset = 0) const override;
    virtual Field fromSql(const QSqlRecord& record) const  override;


};
}
#endif // FIELDDATAMAPPER_H
