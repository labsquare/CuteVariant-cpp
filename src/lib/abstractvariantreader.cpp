#include "abstractvariantreader.h"
namespace cvar{

AbstractVariantReader::AbstractVariantReader(const QString &filename)
{
    mDevice = new QFile(filename);
    mFilename = filename;
}

AbstractVariantReader::AbstractVariantReader(QIODevice *device)
{
    mDevice = device;
    mFilename.clear();
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
