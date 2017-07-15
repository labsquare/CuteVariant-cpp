#include "vcfvariantreader.h"
namespace core {
VCFVariantReader::VCFVariantReader(const QString &filename)
    :AbstractVariantReader(filename)
{

}

QList<Field> VCFVariantReader::fields()
{

}

QList<Sample> VCFVariantReader::samples()
{
    QList<Sample> samples;

    if ( device()->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device());

        while (!stream.atEnd())
        {
            // detect the following pattern :
            // #CHROM	POS	ID	REF	ALT	QUAL	FILTER	INFO	FORMAT	BLANK	NA12878	NA12891	NA12892	NA19238	NA19239	NA19240

            QString line = stream.readLine();
            if (line.startsWith("#CHROM"))
            {
                QStringList header = line.split(QChar::Tabulation);
                if (header.size() > 9)
                {
                    qDebug()<<header.size();
                    for (int i = 9 ; i< header.size(); ++i)
                        samples.append(Sample(header.at(i)));
                }
                break;
            }
        }
        device()->close();
    }
    return samples;
}

bool VCFVariantReader::readVariant(Variant &variant)
{

}

bool VCFVariantReader::readGenotype(Genotype &genotype)
{

}
}
