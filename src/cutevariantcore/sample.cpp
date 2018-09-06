#include "sample.h"
namespace cvar {



Sample::Sample(const QString &name)
{
    setName(name);
}


const QString &Sample::name() const
{

}

void Sample::setName(const QString &name)
{
    mName = name;
}

quint64 Sample::id() const
{
    return mId;
}

void Sample::setId(const quint64 &id)
{
    mId = id;
}



}
