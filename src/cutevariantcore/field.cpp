#include "field.h"
namespace cvar {


const QHash<Field::StandardField, Field> Field::standardFields =
{
    {Chromosom, {"chr","variants","variant chromosome", QVariant::String}},
    {Position, {"pos","variants","variant position", QVariant::String}},
    {Reference, {"ref","variants","reference allele", QVariant::String}},
    {Alternative, {"alt","variants","alternative allele", QVariant::String}},

};




Field::Field(const QString &name, const QString& category, const QString &description, QVariant::Type type)

{
    setName(name);
    setCategory(category);
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

QVariant::Type Field::type() const
{
    return mType;
}

QString Field::typeName() const
{
    return QVariant::typeToName(mType);
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

void Field::setName(const QString &name)
{
    mName = simplified(name);
}

void Field::setDescription(const QString &description)
{
    mDescription = simplified(description);
}

void Field::setType(QVariant::Type type)
{
    mType = type;
}

void Field::setType(const QString &name)
{
    //By default
    setType(QVariant::nameToType(name.toStdString().data()));

    //    if (name == "TEXT")
    //        setType(Field::TEXT);

    //    if (name == "BOOL")
    //        setType(Field::BOOL);

    //    if (name == "INTEGER")
    //        setType(Field::INTEGER);

    //    if (name == "REAL")
    //        setType(Field::REAL);
}

void Field::setCategory(const QString &category)
{
    mCategory = category;
}

bool Field::operator ==(const Field &other)
{
    return name() == other.name();
}

bool Field::isNull() const
{
    return name().isNull();
}

QString Field::expression() const
{
    return mExpression;
}

void Field::setExpression(const QString &expression)
{
    mExpression = expression;
}

quint64 Field::id() const
{
    return mId;
}

void Field::setId(const quint64 &id)
{
    mId = id;
}

Field Field::standardField(Field::StandardField type)
{
    return standardFields.value(type,Field());
}







}
