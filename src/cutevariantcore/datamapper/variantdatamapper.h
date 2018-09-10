#ifndef VARIANTDATAMAPPER_H
#define VARIANTDATAMAPPER_H
#include "datamapper.h"
#include "variant.h"
#include "field.h"

namespace cvar {
class VariantDataMapper: public DataMapper<Variant, VariantDataMapper>
{
public:
    VariantDataMapper();

    virtual Variant read(const QSqlRecord& record) const  override;
    virtual QHash<QString, QVariant> write(const Variant& record) const override;

    virtual bool createTable() const override;

    void setDynamicFields(const QList<Field> &dynamicFields);

private:
    QList<Field> mDynamicFields;


};

}
#endif // VARIANTDATAMAPPER_H
