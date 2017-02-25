#include "variant.h"

Variation::Variation()
{

}

Variation::Variation(const QString &chromosom, quint64 position, const QString &ref, const QString &alt, quint64 quality, QString filter)
    :mChromosom(chromosom), mPosition(position), mRef(ref), mAlt(alt), mQuality(quality),mFilter(filter)

{

}

const QString &Variation::chromosom() const
{
    return mChromosom;
}

quint64 Variation::position() const
{
    return mPosition;
}

const QString &Variation::identifier() const
{
    return mIdentifier;
}

const QString &Variation::ref() const
{
    return mRef;
}

const QString &Variation::alt() const
{
    return mAlt;
}

quint64 Variation::quality() const
{
    return mQuality;
}


const QString &Variation::filter() const
{
    return mFilter;
}

void Variation::clearAnnotation()
{
    mAnnotations.clear();
}

void Variation::addAnnotation(const QString &key, const QVariant &value)
{
    mAnnotations.append(qMakePair(key, value));
}

const QPair<QString, QVariant> &Variation::annotation(int index) const
{
    return mAnnotations.at(index);
}

int Variation::annotationCount() const
{
    return mAnnotations.count();
}


