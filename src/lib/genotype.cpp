#include "genotype.h"
namespace core {

Genotype::Genotype()
    :Resource()
{

}

Genotype::Genotype(const QString &chr, quint64 pos, const QString &ref, const QString &alt, const QString &sampleName, const QString &rawGenotype)
{
    mVariant.setChr(chr);
    mVariant.setPos(pos);
    mVariant.setRef(ref);
    mVariant.setAlt(alt);
    mSample.setName(sampleName);
    mRawGenotype = rawGenotype;

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
            return Type::Homozygous_ref;

        if (a+b == 1)
            return Type::Heterozygous;

        if (a == b )
            return Type::Homozygous_alt;

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



}

