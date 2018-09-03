#include "genotype.h"
namespace cvar {


Genotype::Genotype(const QString &chr, quint64 pos, const QString &ref, const QString &alt, const QString &sampleName)
    :AbstractRecord("genotypes")
{
    mVariant.setChr(chr);
    mVariant.setPos(pos);
    mVariant.setRef(ref);
    mVariant.setAlt(alt);
    mSample.setName(sampleName);

}

void Genotype::setRawGenotype(const QString &raw)
{
    mAnnotations["GT"] = raw;
}

void Genotype::addAnnotation(const QString &colname, const QVariant &value)
{
    mAnnotations.insert(colname, value);
}

void Genotype::clearAnnotation()
{
    mAnnotations.clear();
}

QStringList Genotype::annotationNames() const
{
    return mAnnotations.keys();
}

QVariant Genotype::annotation(const QString &colname) const
{
    return mAnnotations.value(colname, QVariant());
}

QVariant &Genotype::operator[](const QString &colname)
{
    return mAnnotations[colname];
}

Genotype::Type Genotype::type() const
{
    QRegularExpression regexp;
    regexp.setPattern(QStringLiteral("(.+)(\\||/)(.+)"));

    QRegularExpressionMatch match = regexp.match(mRawGenotype);

    if (match.capturedLength() == 3)
    {

        int a = match.captured(1).toInt();
        int b = match.captured(3).toInt();

        if ( a+b == 0)
            return Genotype::Type::Homozygous_ref;

        if (a+b == 1)
            return Genotype::Type::Heterozygous;

        if (a == b )
            return Genotype::Type::Homozygous_alt;

        if ( a != b && (a == 0 || b ==0))
            return Type::Heterozygous;

        return Type::Double_alt;

    }
    return Homozygous_alt;

}

QString Genotype::typeName() const
{
    if ( type() == Homozygous_alt)
        return "Homozygous_alt";

    if ( type() == Homozygous_ref)
        return "Homozygous_ref";

    if ( type() == Heterozygous)
        return "Heterozygous";

    if ( type() == Double_alt)
        return "Double_alt";

    return "Unknown";
}

bool Genotype::isHomo() const
{
    return (type() == Homozygous_alt || type() == Homozygous_ref);
}

bool Genotype::isHetero() const
{
    return (type() == Heterozygous || type() == Double_alt);

}

bool Genotype::isNull() const
{
    return mVariant.isNull();
}

const Sample &Genotype::sample() const
{
    return mSample;
}

const Variant &Genotype::variant() const
{
    return mVariant;
}

QString Genotype::rawGenotype() const
{
    return mAnnotations.value("GT", "!/!").toString();
}

bool Genotype::update()
{

}

bool Genotype::insert()
{

}

bool Genotype::remove()
{

}

void Genotype::fromSql(const QSqlRecord &record)
{

}



}

