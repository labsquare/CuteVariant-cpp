#include "region.h"

Region::Region()
{

}

Region::Region(const QString &chromosom, quint64 start, quint64 end)
    : mChromosom(chromosom), mStart(start), mEnd(end)
{

}

const QString &Region::chromosom() const
{
    return mChromosom;
}

void Region::setChromosom(const QString &chromosom)
{
    mChromosom = chromosom;
}

quint64 Region::start() const
{
    return mStart;
}

void Region::setStart(const quint64 &start)
{
    mStart = start;
}

quint64 Region::end() const
{
    return mEnd;
}

void Region::setEnd(const quint64 &end)
{
    mEnd = end;
}

quint64 Region::size() const
{
    return mEnd - mStart;
}
