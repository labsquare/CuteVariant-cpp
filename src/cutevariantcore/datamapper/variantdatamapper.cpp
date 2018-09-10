#include "variantdatamapper.h"

namespace cvar {
VariantDataMapper::VariantDataMapper()
    :DataMapper<Variant, VariantDataMapper>("variants")
{

}

Variant VariantDataMapper::read(const QSqlRecord &record) const
{

}

QHash<QString, QVariant> VariantDataMapper::write(const Variant &record) const
{

}

bool VariantDataMapper::createTable() const
{

    if (mDynamicFields.isEmpty())
    {
        qWarning()<<Q_FUNC_INFO<<"Cannot create variant table. No dynamic fields set";
        return false;
    }

    return DataMapper<Variant, VariantDataMapper>::createTable();


}

void VariantDataMapper::setDynamicFields(const QList<Field> &dynamicFields)
{
    mDynamicFields = dynamicFields;

    for (const Field& f : mDynamicFields){

        qDebug()<<DataColumn::typeFromQt(f.type());

        addColumn(f.colname(), DataColumn::typeFromQt(f.type()));

    }

}
}