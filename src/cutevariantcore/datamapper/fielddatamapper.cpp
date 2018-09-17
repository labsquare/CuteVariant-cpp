#include "fielddatamapper.h"
#include "field.h"
namespace cvar {

FieldDataMapper::FieldDataMapper()
    :DataMapper<Field, FieldDataMapper>("fields")
{
    addColumn("colname", DataColumn::Text, "NOT NULL");
    addColumn("description", DataColumn::Text);
    addColumn("type", DataColumn::Text);

}

QHash<QString, QVariant> FieldDataMapper::toSql(const Field &record) const
{

    return {

        {"colname", record.colname()},
        {"description", record.description()},
        {"type", record.typeName()}

    };


}

Field FieldDataMapper::fromSql(const QSqlRecord &record) const
{

    Field field;
    field.setId(quint64(record.value("rowid").toInt()));
    field.setColname(record.value("colname").toString());
    field.setDescription(record.value("description").toString());
    field.setType(record.value("type").toString());

    return field;

}

}
