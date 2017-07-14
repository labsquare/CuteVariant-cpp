#include "field.h"

Field::Field()
    :Resource()
{

}

Field::Field(const QString &name, const QString &description)
    :Resource(),mName(name), mDescription(description)
{

}

const QString &Field::name() const
{
    return mName;
}

const QString &Field::description() const
{
    return mDescription;
}



