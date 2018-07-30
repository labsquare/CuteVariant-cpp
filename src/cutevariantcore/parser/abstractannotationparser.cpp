#include "abstractannotationparser.h"

namespace cvar {
AbstractAnnotationParser::AbstractAnnotationParser(const QString &label)
    :mLabel(label)
{

}

QString AbstractAnnotationParser::label() const
{
    return mLabel;
}

}
