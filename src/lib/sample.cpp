#include "sample.h"
namespace core {
Sample::Sample()
    :Resource()
{

}

Sample::Sample(const QString &name)
    :Resource(), mName(name)
{

}

QVariant Sample::phenotype(const QString &key)
{
    return mPhenotype.value(key);
}

const QString &Sample::name() const
{
    return mName;
}
}
