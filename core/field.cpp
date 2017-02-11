#include "field.h"

Field::Field()
{

}

Field::Field(const QString &name, const QString &description)
    :mName(name), mDescription(description)
{

}

QString Field::name() const
{
    return mName;
}

void Field::setName(const QString &name)
{
    mName = name;
}

QString Field::description() const
{
    return mDescription;
}

void Field::setDescription(const QString &description)
{
    mDescription = description;
}

int Field::id() const
{
    return mId;
}

void Field::setId(int id)
{
    mId = id;
}
