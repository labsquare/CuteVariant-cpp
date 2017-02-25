#include "field.h"

Field::Field()
{

}

Field::Field(int sqlId, const QString &name, const QString &description)
    :msqlId(sqlId), mName(name), mDescription(description)
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

int Field::sqlId() const
{
    return msqlId;
}



