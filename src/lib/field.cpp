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
    :Resource()
{
    setColname(colname);
    setName(name);
    setDescription(description);
    setType(type);
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

    if (type() == Field::BOOL)
        return "BOOL";

    return "TEXT";
}

QString Field::sqliteType() const
{
    if (type() == Field::TEXT)
        return "TEXT";

    if (type() == Field::REAL)
        return "REAL";

    if (type() == Field::INTEGER)
        return "INTEGER";

    // Sqlite doesn't have bool type
    if (type() == Field::BOOL)
        return "INTEGER";

    return "TEXT";

}

QString Field::category() const
{
 return mCategory;
}

QString Field::simplified(const QString &name)
{
    // remove white space
    QString out = name.simplified();

    // replace "." by "_"
    out =  out.replace(".","_");
    out = out.remove("'");
    out = out.remove("\"");

    return out;

}

void Field::setColname(const QString &colname)
{
    // save only the first world for sql syntax..
    QRegularExpression exp("([^\\s]+)");
    mColname = exp.match(simplified(colname)).captured(1).toUpper();
}

void Field::setName(const QString &name)
{
    mName = simplified(name);
}

void Field::setDescription(const QString &description)
{
    mDescription = simplified(description);
}

void Field::setType(Field::Type type)
{
    mType = type;
}

void Field::setType(const QString &name)
{
    //By default
    setType(Field::TEXT);

    if (name == "TEXT")
        setType(Field::TEXT);

    if (name == "BOOL")
        setType(Field::BOOL);

    if (name == "INTEGER")
        setType(Field::INTEGER);

    if (name == "REAL")
        setType(Field::REAL);
}

void Field::setCategory(const QString &category)
{
    mCategory = category;
}

bool Field::operator ==(const Field &other)
{
    return colname() == other.colname();
}



}
