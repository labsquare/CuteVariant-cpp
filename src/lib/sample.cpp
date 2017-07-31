#include "sample.h"
namespace cvar {
Sample::Sample()
    :Resource()
{

}

Sample::Sample(const QString &name)
    :Resource()
{
    setName(name);
}

QVariant Sample::phenotype(const QString &key)
{
    return mPhenotype.value(key);
}

const QString &Sample::name() const
{
    return mName;
}

void Sample::setName(const QString &name)
{
    mName = name;
}
}
