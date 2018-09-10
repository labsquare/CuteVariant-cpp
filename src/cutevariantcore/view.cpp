#include "view.h"

namespace cvar{


View::View(const QString &name, const QString &description, int count)
     :mName(name), mDescription(description), mCount(count)
{

}

QString View::name() const
{
    return mName;
}

void View::setName(const QString &name)
{
    mName = name;
}

QString View::description() const
{
    return mDescription;
}

void View::setDescription(const QString &description)
{
    mDescription = description;
}

int View::count() const
{
    return mCount;
}

void View::setCount(int count)
{
    mCount = count;
}

QString View::sql() const
{
    return mSql;
}

void View::setSql(const QString &sql)
{
    mSql = sql;
}

quint64 View::id() const
{
    return mId;
}

void View::setId(const quint64 &id)
{
    mId = id;
}


}
