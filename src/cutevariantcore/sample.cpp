#include "sample.h"
namespace cvar {



Sample::Sample(const QString &name)
{
    setName(name);
}

QVariant Sample::phenotype(const QString &key)
{
    return mPhenotype.value(key);
}

const QString &Sample::name() const
{

}

void Sample::setName(const QString &name)
{
    mName = name;
}



}
