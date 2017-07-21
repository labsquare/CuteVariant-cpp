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

void Resource::setTableName(const QString &name)
{
    mTableName = name;
}
}
