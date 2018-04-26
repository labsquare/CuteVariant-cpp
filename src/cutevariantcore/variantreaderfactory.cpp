#include "variantreaderfactory.h"

namespace cvar {
AbstractVariantReader *VariantReaderFactory::createVariantReader(const QString &filename)
{

    if (!QFile::exists(filename))
        return nullptr;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {

        if (isVcf(&file))
        {
            if (isVep(&file))
                return new VepVcfReader(filename);

            if (isSnpEff(&file))
                return new SnpEffVCFReader(filename);

            return new GenericVCFReader(filename);
        }

        if (isAnnovar(&file))
            return nullptr;

    }

    return nullptr;
}

bool VariantReaderFactory::isVcf(QIODevice * device)
{
    QTextStream stream(device);
    QString line;

    while (line.startsWith("##")){
        line = stream.readLine().toLower();

        if (line.startsWith("##fileformat=vcf.+"))
            return true;
    }
    return false;

}

bool VariantReaderFactory::isSnpEff(QIODevice *device)
{

    QTextStream stream(device);
    QString line;

    while (line.startsWith("##")){
        line = stream.readLine().toLower();

        if (line.startsWith("##Snpeffversion=.+"))
            return true;
    }
    return false;


}

bool VariantReaderFactory::isVep(QIODevice *device)
{
    QTextStream stream(device);
    QString line;

    while (line.startsWith("##")){
        line = stream.readLine().toLower();

        if (line.startsWith("##vep=.+"))
            return true;
    }
    return false;
}

bool VariantReaderFactory::isAnnovar(QIODevice *device)
{
    return false;
}

VariantReaderFactory::VariantReaderFactory()
{

}
}
