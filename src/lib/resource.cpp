#include "resource.h"
namespace core {
Resource::Resource()
{

}

quint64 Resource::id() const
{
    return mId;
}

const QString &Resource::tableName() const
{
    return mTableName;
}

void Resource::setId(quint64 id)
{
    mId = id;
}

void Resource::setTableName(const QString &name)
{
    mTableName = name;
}
}
