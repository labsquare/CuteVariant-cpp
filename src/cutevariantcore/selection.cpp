#include "selection.h"

namespace cvar{

VariantSet::VariantSet()
{

}

VariantSet::VariantSet(const QString &name, const QString &description, int count)
    :mName(name), mDescription(description), mCount(count)
{

}

QString VariantSet::name() const
{
    return mName;
}

void VariantSet::setName(const QString &name)
{
    mName = name;
}

QString VariantSet::description() const
{
    return mDescription;
}

void VariantSet::setDescription(const QString &description)
{
    mDescription = description;
}

int VariantSet::count() const
{
    return mCount;
}

void VariantSet::setCount(int count)
{
    mCount = count;
}

QString VariantSet::sql() const
{
    return mSql;
}

void VariantSet::setSql(const QString &sql)
{
    mSql = sql;
}

}
