#include "bedfile.h"
namespace cvar {
BedFile::BedFile()
    :Resource()
{

}

BedFile::BedFile(const QString &filename, int count)
    :Resource(), mFilename(filename), mCount(count)
{

}

const QString &BedFile::filename() const
{
    return mFilename;
}

void BedFile::setFilename(const QString &filename)
{
    mFilename = filename;
}

quint64 BedFile::count() const
{
    return mCount;
}

void BedFile::setCount(const quint64 &count)
{
    mCount = count;
}

}
