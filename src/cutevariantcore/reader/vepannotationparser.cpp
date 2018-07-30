#include "vepannotationparser.h"

namespace cvar{
VepAnnotationParser::VepAnnotationParser(const QString& label)
    :AbstractAnnotationParser(label)
{

}

QList<Field> VepAnnotationParser::parseFields(const Field &field)
{
    mAnnFields.clear();
    QRegularExpression exp("Allele.+");
    QRegularExpressionMatch match = exp.match(field.description());

    if (match.hasMatch())
    {
        for (QString& name : match.captured().split("|"))
        {
            // remove trailing space
            name = name.simplified().toLower();

            // rename standard
            if (standardField.contains(name))
                mAnnFields.append(standardField[name]);
            else
                mAnnFields.append(Field(name,"ANN",name));
        }
    }

    return mAnnFields;

}

QList<Variant> VepAnnotationParser::parseVariant(Variant &variant)
{
    QList<Variant> variants;

    QString rawAnn = variant[label()].toString();

    // split by allele
    for (QString alleleAnn : rawAnn.split(","))
    {
        Variant newVariant = variant;
        newVariant.removeAnnotation(label());

        // split annotation
        QStringList annValues = alleleAnn.split("|");


        if ( annValues.size() != mAnnFields.size())
            qCritical()<<"Fields and annotation values count mismatch";

        // avoid memory leak => use qMin index
        for (int i=0; i< qMin(annValues.size(), mAnnFields.size()); ++i)
        {

            QString fname = mAnnFields[i].name();
            QString value = annValues[i];


            // remove hgvs prefix
            if (fname.startsWith("hgvs"))
                value.remove(QRegularExpression(".+:"));

            newVariant[fname] = value;

        }

        variants.append(newVariant);
    }
    return variants;
}


}
