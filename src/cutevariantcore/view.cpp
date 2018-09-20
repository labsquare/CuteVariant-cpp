#include "view.h"

namespace cvar{


View::View(const QString &name, const QString &description, int count, const QString &sql)
    :mName(name), mDescription(description), mCount(count), mSql(sql)
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

View View::unionWith(const View &other) const
{
    qDebug()<<other.sql();
    View view(other.name() + "u" + name());
    view.setSql(QString("SELECT rowid, * FROM `variants` WHERE rowid IN (SELECT rowid FROM (%1) UNION SELECT rowid FROM (%2))").arg(this->sql()).arg(other.sql()));
    return view;
}

View View::intersectWith(const View &other) const
{
    View view(other.name() + "&" + name());
    view.setSql(QString("SELECT rowid, * FROM `variants` WHERE rowid IN (SELECT rowid FROM (%1) INTERSECT SELECT rowid FROM (%2))").arg(sql(), other.sql()));
    return view;
}

View View::exceptWith(const View &other) const
{
    View view(other.name() + "e" + name());
    view.setSql(QString("SELECT rowid, * FROM `variants` WHERE rowid IN (SELECT rowid FROM (%1) EXCEPT SELECT rowid FROM (%2))").arg(sql(), other.sql()));
    return view;
}

View View::operator+(const View &other) const
{
    return this->unionWith(other);
}

View View::operator-(const View &other) const
{
    return this->exceptWith(other);
}

View View::operator&(const View &other) const
{
    return this->intersectWith(other);
}


}
