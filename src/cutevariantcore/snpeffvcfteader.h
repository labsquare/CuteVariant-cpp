#ifndef SNPEFFVCFREADER_H
#define SNPEFFVCFREADER_H
#include <QtCore>
#include "genericvcfreader.h"
#include "variant.h"

namespace cvar {

class SnpEffVCFReader : public GenericVCFReader
{
public:
    SnpEffVCFReader(const QString& filename);
    SnpEffVCFReader(QIODevice *device);

    virtual QList<Field> fields() override;

    virtual Variant readVariant() override;



protected:
    QVector<Variant> parseVariantAnnotation(const Variant& variant);

    // multiple annotation per line of variant. duplicate variant for each annotation
    QVector<Variant> mDuplicateVariantsPerAnnotation;
};
}

#endif // SNPEFFVCFREADER_H
