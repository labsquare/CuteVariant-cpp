#include "variant.h"
namespace core {
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
