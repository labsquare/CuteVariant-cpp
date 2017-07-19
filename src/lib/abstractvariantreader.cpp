#include "abstractvariantreader.h"
namespace core{
AbstractVariantReader::AbstractVariantReader(const QString &filename)
{
    mDevice = new QFile(filename);
    mFilename = filename;
}

bool AbstractVariantReader::open()
{
    return device()->open(QIODevice::ReadOnly);



}

void AbstractVariantReader::close()
{
    device()->close();
}

bool AbstractVariantReader::atEnd()
{
    return device()->atEnd();
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
