#include "fielddatamapper.h"
#include "field.h"
namespace cvar {

FieldDataMapper::FieldDataMapper()
    :DataMapper<Field, FieldDataMapper>("fields")
{
    addColumn("name", DataColumn::Text, "NOT NULL");
    addColumn("category", DataColumn::Text,"DEFAULT variants");
    addColumn("description", DataColumn::Text);
    addColumn("type", DataColumn::Text);

}

QHash<QString, QVariant> FieldDataMapper::toSql(const Field &record) const
{

    return {

        {"name", record.name()},
        {"category", record.category()},
        {"description", record.description()},
        {"type", record.typeName()}

    };


}

Field FieldDataMapper::fromSql(const QSqlRecord &record) const
{

    Field field;
    field.setId(quint64(record.value("rowid").toInt()));
    field.setName(record.value("name").toString());
    field.setCategory(record.value("category").toString());
    field.setDescription(record.value("description").toString());
    field.setType(record.value("type").toString());

    return field;

}



}
