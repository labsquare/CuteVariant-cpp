#ifndef VEPANNOTATIONPARSER_H
#define VEPANNOTATIONPARSER_H
#include "abstractannotationparser.h"

namespace cvar{

class VepAnnotationParser : public AbstractAnnotationParser
{
public:
    VepAnnotationParser();

    virtual QList<Field> parseFields(const Field& field);
    virtual QList<Variant> parseVariant(Variant &variant);


};

}
#endif // VEPANNOTATIONPARSER_H
