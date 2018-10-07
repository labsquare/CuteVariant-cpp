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

    virtual Variant fromSql(const QSqlRecord& record) const  override;
    virtual QHash<QString, QVariant> toSql(const Variant& record) const override;


    void setDynamicFields(const QList<Field> &dynamicFields);

private:
    QList<Field> mDynamicFields;
    const QStringList mIgnoreField = {"chr","pos","ref","alt"};


};

}
#endif // VARIANTDATAMAPPER_H
