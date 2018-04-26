#ifndef VEPVCFREADER_H
#define VEPVCFREADER_H

#include <QtCore>
#include "genericvcfreader.h"
#include "variant.h"


namespace cvar {
class VepVcfReader: public GenericVCFReader
{
public:
    VepVcfReader(const QString& filename);
    VepVcfReader(QIODevice * device);

    virtual QList<Field> fields() override;
    virtual Variant readVariant() override;


protected:
    QList<Field> parseFieldAnnotation(const Field& field);
    QVector<Variant> parseVariantAnnotation(const Variant& variant);

    // multiple annotation per line of variant. duplicate variant for each annotation
    QVector<Variant> mDuplicateVariantsPerAnnotation;





};

}
#endif // VEPVCFREADER_H
