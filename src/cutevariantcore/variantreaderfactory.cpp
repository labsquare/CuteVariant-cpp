#include "variantreaderfactory.h"

namespace cvar {
AbstractVariantReader *VariantReaderFactory::createVariantReader(const QString &filename)
{

    if (!QFile::exists(filename))
        return nullptr;

    auto format = fileFormat(filename);


    if (format == VariantReaderFactory::Vcf)
        return new GenericVCFReader(new QFile(filename));

    if (format == VariantReaderFactory::SnpEff)
    {
        auto reader = new GenericVCFReader(new QFile(filename));
        reader->addAnnotationParser(new SnpEffAnnotationParser());
        return reader;
    }


    if (format == VariantReaderFactory::Vep)
    {
        auto reader = new GenericVCFReader(new QFile(filename));
        reader->addAnnotationParser(new VepAnnotationParser());
        return reader;

    }

    return nullptr;
}

VariantReaderFactory::Format VariantReaderFactory::fileFormat(const QString &filename)
{

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical()<<Q_FUNC_INFO<<"cannot open file" ;
        return VariantReaderFactory::Unknown;
    }

    if (isSnpEff(&file))
        return VariantReaderFactory::SnpEff;

    if (isVep(&file))
        return VariantReaderFactory::Vep;


    if (isVcf(&file))
        return VariantReaderFactory::Vcf;



    return VariantReaderFactory::Unknown;

}


bool VariantReaderFactory::isVcf(QIODevice * device)
{
    device->reset();
    QTextStream stream(device);
    QString line;

    do {
        line = stream.readLine().toLower();
        if (line.startsWith("##fileformat=vcf"))
            return true;
    } while (line.startsWith("##"));


    return false;

}

bool VariantReaderFactory::isSnpEff(QIODevice *device)
{
    device->reset();

    QTextStream stream(device);
    QString line;

    do {
        line = stream.readLine().toLower();
        if (line.startsWith("##snpeffversion="))
            return true;
    } while (line.startsWith("##"));

    return false;


}

bool VariantReaderFactory::isVep(QIODevice *device)
{
    QTextStream stream(device);
    QString line;


    do {
        line = stream.readLine().toLower();
        if (line.startsWith("##vep="))
            return true;
    } while (line.startsWith("##"));

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
}
