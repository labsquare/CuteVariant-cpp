#include "sample.h"

Sample::Sample()
    :Resource()
{

}

Sample::Sample(const QString &name)
    :Resource()
{

}

QVariant Sample::phenotype(const QString &key)
{
    return mPhenotype.value(key);
}
