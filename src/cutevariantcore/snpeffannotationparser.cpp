#include "snpeffannotationparser.h"

namespace cvar{
SnpEffAnnotationParser::SnpEffAnnotationParser()
    :AbstractAnnotationParser("ANN")
{

}

QList<Field> SnpEffAnnotationParser::parseFields(const Field &field)
{
    mAnnFields.clear();
    QRegularExpression exp("Allele.+");
    QRegularExpressionMatch match = exp.match(field.description());

    if (match.hasMatch())
    {
        for (QString& name : match.captured().split("|"))
        {
            name = name.simplified().toLower();

            // rename
            name =nameMap.value(name,name);

            mAnnFields.append(Field("ANN_"+name, name));
        }
    }

    return mAnnFields;
}

QList<Variant> SnpEffAnnotationParser::parseVariant(Variant &variant)
{
    QList<Variant> variants;

    QString rawAnn = variant[infoName()].toString();

    // split by allele
    for (QString alleleAnn : rawAnn.split(","))
    {
        Variant newVariant = variant;
        newVariant.removeAnnotation(infoName());

        // split annotation
        QStringList annValues = alleleAnn.split("|");


        if ( annValues.size() != mAnnFields.size()){

            qCritical()<<"ICI "<<annValues.size()<<" "<<mAnnFields.size();
            qCritical()<<"Field and annotation values count mismatch";

        }


        // avoid memory leak => use qMin index
        for (int i=0; i< qMin(annValues.size(), mAnnFields.size()); ++i)
            newVariant[mAnnFields[i].name()] = annValues[i];

        variants.append(newVariant);
    }
    return variants;
}
}
