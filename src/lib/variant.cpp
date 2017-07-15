#include "variant.h"
namespace core {
Variant::Variant()
    :Resource()
{

}

Variant::Variant(const QString &chr, quint64 pos, QByteArray &ref, QByteArray &alt)
    :Resource(), mChr(chr), mPos(pos), mRef(ref), mAlt(alt)
{

}

void Variant::addAnnotation(const QString &key, const QVariant &value)
{
    mAnnotations.insert(key,value);
}

void Variant::clearAnnotation()
{
    mAnnotations.clear();
}

const QString &Variant::chromosom() const
{
    return mChr;
}

quint64 Variant::position() const
{
    return mPos;
}

const QByteArray &Variant::ref() const
{
    return mRef;
}

const QByteArray &Variant::alt() const
{
    return mAlt;
}
}
