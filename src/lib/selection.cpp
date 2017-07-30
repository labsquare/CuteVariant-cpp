#include "selection.h"

namespace core{

VariantSelection::VariantSelection()
{

}

VariantSelection::VariantSelection(const QString &name, const QString &description, int count)
    :mName(name), mDescription(description), mCount(count)
{

}

QString VariantSelection::name() const
{
    return mName;
}

void VariantSelection::setName(const QString &name)
{
    mName = name;
}

QString VariantSelection::description() const
{
    return mDescription;
}

void VariantSelection::setDescription(const QString &description)
{
    mDescription = description;
}

int VariantSelection::count() const
{
    return mCount;
}

void VariantSelection::setCount(int count)
{
    mCount = count;
}

QString VariantSelection::sql() const
{
    return mSql;
}

void VariantSelection::setSql(const QString &sql)
{
    mSql = sql;
}

}
