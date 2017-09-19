#include "resource.h"
namespace cvar {
Resource::Resource()
{

}

qint64 Resource::id() const
{
    return mId;
}

const QString &Resource::tableName() const
{
    return mTableName;
}

void Resource::setId(qint64 id)
{
    mId = id;
}

QString Resource::normalize(const QString &string)
{
    // remove white space
    QString out = string.simplified();

    // replace "." by "_"
    out = out.replace(".","_");
    // remove quote
    out = out.remove("'");
    out = out.remove("\"");
    return out;
}

bool Resource::exists() const
{
    return id() != -1;
}

void Resource::setTableName(const QString &name)
{
    mTableName = name;
}
}
