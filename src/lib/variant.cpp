#include "variant.h"
namespace cvar {
Variant::Variant()
    :Resource()
{

}

Variant::Variant(const QString &chr, quint64 pos, QString &ref, QString &alt)
    :Resource(), mChr(chr), mPos(pos), mRef(ref), mAlt(alt)
{

}

void Variant::addAnnotation(const QString& colname, const QVariant &value)
{   
    mAnnotations.insert(colname, value);
}

void Variant::clearAnnotation()
{
    mAnnotations.clear();
}

QVariant Variant::annotation(const QString &colname) const
{
    return mAnnotations.value(colname,QVariant());
}

QVariant& Variant::operator[](const QString &colname)
{
    return mAnnotations[colname];
}

bool Variant::operator==(const Variant &v1)
{
    return name() == v1.name();
}

void Variant::setChr(const QString &chr)
{
    mChr = chr;
}

void Variant::setPos(quint64 pos)
{
    mPos = pos;
}

void Variant::setRef(const QString &ref)
{
    mRef = ref;
}

void Variant::setAlt(const QString &alt)
{
    mAlt = alt;
}

void Variant::setRsId(const QString &rsid)
{
    mRsId = rsid;
}

void Variant::setQual(double qual)
{
    mQual = qual;
}

bool Variant::isNull() const
{
    return chromosom().isEmpty();
}

QString Variant::name() const
{
    return QString("%1-%2-%3-%4").arg(chromosom()).arg(position()).arg(ref()).arg(alt());
}

QString Variant::coordinate() const
{
    return QString("%1:%2").arg(mChr).arg(mPos);
}

QUrl Variant::igvUrl() const
{
    return QUrl(QString("http://localhost:60151/locus?%1:%2").arg(chromosom()).arg(position()));
}

QUrl Variant::varsomeUrl() const
{
    return QUrl(QString("https://varsome.com/variant/hg19/%2").arg(name()));

}

void Variant::setFilter(const QString &filter)
{
    mFilter = filter;
}

const QString &Variant::chromosom() const
{
    return mChr;
}

quint64 Variant::position() const
{
    return mPos;
}

const QString& Variant::rsId() const
{
    return mRsId;
}

const QString& Variant::filter() const
{
    return mFilter;
}

double Variant::qual() const
{
    return mQual;
}

const QString &Variant::ref() const
{
    return mRef;
}

const QString &Variant::alt() const
{
    return mAlt;
}
}
