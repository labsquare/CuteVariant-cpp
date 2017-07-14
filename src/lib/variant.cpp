#include "variant.h"

Variant::Variant()
    :Resource()
{

}

Variant::Variant(const QString &chr, quint64 pos, QByteArray &ref, QByteArray &alt)
    :Resource(), mChr(chr), mPos(pos), mRef(ref), mAlt(alt)
{

}
