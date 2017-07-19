#include "field.h"
namespace core {
Field::Field()
    :Resource()
{

}

const QString &Field::colname() const
{
    return mColname;
}

Field::Field(const QString& colname,const QString &name, const QString &description, const Type& type)
    :Resource(),mColname(colname), mName(name), mDescription(description), mType(type)
{

}

const QString &Field::name() const
{
    return mName;
}

const QString &Field::description() const
{
    return mDescription;
}

Field::Type Field::type() const
{
    return mType;
}

QString Field::typeName() const
{
  if (type() == Field::TEXT)
      return "TEXT";

  if (type() == Field::REAL)
      return "REAL";

  if (type() == Field::INTEGER)
      return "INTEGER";

  return "TEXT";

}

}
