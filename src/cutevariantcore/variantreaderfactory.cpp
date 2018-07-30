#include "variantreaderfactory.h"

namespace cvar {
AbstractVariantReader *VariantReaderFactory::createVariantReader(QIODevice * device, cvar::VariantReaderFactory::Format format)
{

    auto selectFormat = format;

    // if unknwown format, try to detect
    if (selectFormat == VariantReaderFactory::Unknown)
        selectFormat = detectFormat(device);

    // if still no detection, return null
    if (selectFormat == VariantReaderFactory::Unknown)
    {
        qCritical()<<Q_FUNC_INFO<<"cannot detect format";
        return nullptr;
    }


    if (selectFormat == VariantReaderFactory::Vcf)
        return new GenericVCFReader(device);

    if (selectFormat == VariantReaderFactory::SnpEff)
    {
        auto reader = new GenericVCFReader(device);
        reader->addAnnotationParser(new SnpEffAnnotationParser());
        return reader;
    }


    if (selectFormat == VariantReaderFactory::Vep)
    {
        auto reader = new GenericVCFReader(device);
        reader->addAnnotationParser(new VepAnnotationParser());
        return reader;

    }

    return nullptr;
}

VariantReaderFactory::Format VariantReaderFactory::detectFormat(QIODevice * device)
{

    if (isSnpEff(device))
        return VariantReaderFactory::SnpEff;

    if (isVep(device))
        return VariantReaderFactory::Vep;

    if (isVcf(device))
        return VariantReaderFactory::Vcf;

    return VariantReaderFactory::Unknown;
}

bool VariantReaderFactory::isVcf(QIODevice * device)
{
    if (device->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device);
        QString line;

        do {
            line = stream.readLine().toLower();
            if (line.startsWith("##fileformat=vcf"))
            {
                device->close();
                return true;
            }
        } while (line.startsWith("##"));
    }
    device->close();
    return false;

}

bool VariantReaderFactory::isSnpEff(QIODevice *device)
{

    if (device->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device);
        QString line;

        do {
            line = stream.readLine().toLower();
            if (line.startsWith("##snpeffversion="))
            {
                device->close();
                return true;
            }
        } while (line.startsWith("##"));
    }
    device->close();
    return false;
}

bool VariantReaderFactory::isVep(QIODevice *device)
{
    if (device->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device);
        QString line;

        do {
            line = stream.readLine().toLower();
            if (line.startsWith("##vep="))
            {
                device->close();
                return true;


            }
        } while (line.startsWith("##"));
    }
    device->close();
    return false;
}

bool VariantReaderFactory::isAnnovar(QIODevice *device)
{
    return false;
}

VariantReaderFactory::VariantReaderFactory()
    :QObject(nullptr)
{

}


bool VariantReaderFactory::isGzip(QIODevice *device)
{

    if (device->open(QIODevice::ReadOnly))
    {
        QByteArray magic_number = device->read(2);
        device->close();

        if (magic_number.length() < 2)
            return false;

        return static_cast<unsigned char>(magic_number.at(0)) == 0x1f && static_cast<unsigned char>(magic_number.at(1)) == 0x8b;
    }
    else
    {
        return false;
    }


}

}
