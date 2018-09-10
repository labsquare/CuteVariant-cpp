#include "fielddatamapper.h"
#include "field.h"
namespace cvar {

FieldDataMapper::FieldDataMapper()
    :DataMapper<Field, FieldDataMapper>("fields")
{

    addColumn("name", QVariant::String, "NOT NULL");

}

bool cvar::FieldDataMapper::insert(const QList<Field> &records) const
{


}

bool cvar::FieldDataMapper::update(const Field &record) const
{

}

bool cvar::FieldDataMapper::remove(const Field &record) const
{

}

bool cvar::FieldDataMapper::createTable() const
{
    QSqlQuery query;

}

Field cvar::FieldDataMapper::fromSql(const QSqlRecord &record) const
{
    Field field;

    field.setColname(record.value("colname").toString());
    field.setName(record.value("name").toString());
    field.setCategory(record.value("category").toString());
    field.setType(record.value("type").toString());

    return field;

}
}
