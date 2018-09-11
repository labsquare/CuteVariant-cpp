#include "fielddatamapper.h"
#include "field.h"
namespace cvar {

FieldDataMapper::FieldDataMapper()
    :DataMapper<Field, FieldDataMapper>("fields")
{

    addColumn("colname", DataColumn::Text, "NOT NULL");
    addColumn("name", DataColumn::Text, "NOT NULL");
    addColumn("description", DataColumn::Text);
    addColumn("category", DataColumn::Text);
    addColumn("type", DataColumn::Text);


}

QHash<QString, QVariant> FieldDataMapper::toSql(const Field &record) const
{

    return {

        {"colname", record.colname()},
        {"name", record.name()},
        {"description", record.description()},
        {"category", record.category()},
        {"type", record.typeName()}

    };


}

Field FieldDataMapper::fromSql(const QSqlRecord &record) const
{

    Field field;
    field.setId(record.value("rowid").toInt());
    field.setColname(record.value("colname").toString());
    field.setName(record.value("name").toString());
    field.setDescription(record.value("description").toString());
    field.setType(record.value("type").toString());

    return field;

}

}
