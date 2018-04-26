#include "abstractannotationparser.h"

namespace cvar {
AbstractAnnotationParser::AbstractAnnotationParser(const QString &infoName)
    :mInfoName(infoName)
{

}

bool AbstractAnnotationParser::isParsable(const QString &infoName)
{
    if (infoName == mInfoName)
        return true;

    return false;
}



}
