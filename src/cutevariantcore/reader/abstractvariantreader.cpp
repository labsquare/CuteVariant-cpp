#include "abstractvariantreader.h"
namespace cvar{

AbstractVariantReader::AbstractVariantReader(QIODevice *device)
{
    mDevice = device;

}

//bool AbstractVariantReader::open()
//{
//    return device()->open(QIODevice::ReadOnly);
//}

//void AbstractVariantReader::close()
//{
//    device()->close();
//}

//bool AbstractVariantReader::atEnd()
//{
//    return device()->atEnd();
//}

QIODevice * AbstractVariantReader::device() const
{
    return mDevice;
}

}
