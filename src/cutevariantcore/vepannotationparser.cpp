#include "vepannotationparser.h"

namespace cvar{
VepAnnotationParser::VepAnnotationParser()
    :AbstractAnnotationParser("CSQ")
{

}

QList<Field> VepAnnotationParser::parseFields(const Field &field)
{

    QList<Field> fields;
    QRegularExpression exp("Allele.+");
    QRegularExpressionMatch match = exp.match(field.description());

    if (match.hasMatch())
    {
        for (QString& name : match.captured().split("|"))
        {
            name = name.simplified();
            fields.append(Field("ANN_"+name, name));
        }
    }

    return fields;

}

QList<Variant> VepAnnotationParser::parseVariant(Variant &variant)
{

    return {variant};

}
}
