#include "snpeffoldannotationparser.h"

namespace cvar{
SnpEffOldAnnotationParser::SnpEffOldAnnotationParser(const QString& label)
    :AbstractAnnotationParser(label)
{

}

QList<Field> SnpEffOldAnnotationParser::parseFields(const Field &field)
{
    mAnnFields.clear();
    QRegularExpression exp("Effect_Impact.+");
    QRegularExpressionMatch match = exp.match(field.description());

    if (match.hasMatch())
    {
        for (QString& name : match.captured().split("|"))
        {
            name = name.simplified().toLower();

            // rename
            if (standardField.contains(name))
                mAnnFields.append(standardField[name]);
            else
                mAnnFields.append(Field(name,"ANN",name));
        }
    }

    return mAnnFields;
}

QList<Variant> SnpEffOldAnnotationParser::parseVariant(Variant &variant)
{
    QList<Variant> variants;

    QString rawAnn = variant[this->label()].toString();

    // split by allele
    for (QString alleleAnn : rawAnn.split(","))
    {
        Variant newVariant = variant;
        newVariant.removeAnnotation(this->label());

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
