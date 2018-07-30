#ifndef ANNOTATIONPARSER_H
#define ANNOTATIONPARSER_H
#include "variant.h"
#include "field.h"


namespace cvar {
class AbstractAnnotationParser
{
public:


    AbstractAnnotationParser(const QString& label);


    // parse fields into many fields
    virtual QList<Field> parseFields(const Field& field) = 0;


    // parse annotation variant into many annotation variant
    virtual QList<Variant> parseVariant(Variant& variant) = 0;


    QString label() const;


private:

    // Label is INFO key from VCF File : ex: CSQ; ANN ; EFF ....
    QString mLabel;




};

}
#endif // ANNOTATIONPARSER_H
