#include "abstractvariantreader.h"
namespace core{
AbstractVariantReader::AbstractVariantReader(const QString &filename)
{
    mDevice = new QFile(filename);
    mFilename = filename;
}



const QString &AbstractVariantReader::filename() const
{
    return mFilename;
}

QIODevice * AbstractVariantReader::device() const
{
    return mDevice;
}
}
