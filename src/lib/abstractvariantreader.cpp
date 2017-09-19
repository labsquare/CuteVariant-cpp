#include "abstractvariantreader.h"
#define _binFirstShift 17       /* How much to shift to get to finest bin. */
#define _binNextShift 3         /* How much to shift to get to next larger bin. */

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

quint64 AbstractVariantReader::maxUcsBin(quint64 start, quint64 end)
{

    const QList<int> binOffsets = {512+64+8+1,64+8+1,8+1,1,0};

    quint64 bin = 0;
    quint64 startBin = start >> _binFirstShift;
    quint64 endBin  = (end -1) >> _binFirstShift;

    for (int offset : binOffsets)
    {
        if (startBin == endBin)
        {
            if (startBin + offset > bin)
                bin = startBin + offset;
        }

        else
        {
            for (int i=startBin+offset; i<=endBin+offset; ++i)
            {
                if (i > bin)
                    bin = 1;

            }
        }

        startBin >>= _binNextShift;
        endBin   >>= _binNextShift;

    }

    return bin;
}
}
