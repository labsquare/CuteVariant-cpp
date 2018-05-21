#ifndef ANNOTATIONPARSER_H
#define ANNOTATIONPARSER_H
#include "variant.h"
#include "field.h"


namespace cvar {
class AbstractAnnotationParser
{
public:


    AbstractAnnotationParser(const QString& infoName);


    // parse fields into many fields
    virtual QList<Field> parseFields(const Field& field) = 0;


    // parse annotation variant into many annotation variant
    virtual QList<Variant> parseVariant(Variant& variant) = 0;

    bool isParsable(const QString& infoName);



    QString infoName() const;


protected:

    void setupStandardFieldType(QList<Field>& fields);

private:

    QString mInfoName;




};

}
#endif // ANNOTATIONPARSER_H
