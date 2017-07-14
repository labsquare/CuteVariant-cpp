#include "resource.h"

Resource::Resource()
{

}

quint64 Resource::id() const
{
    return mId;
}

void Resource::setId(quint64 id)
{
    mId = id;
}
