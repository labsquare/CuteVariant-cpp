#include "vcfvariantreader.h"
namespace core {
VCFVariantReader::VCFVariantReader(const QString &filename)
    :AbstractVariantReader(filename)
{

}
//------------------------------------------------------------------
QList<Field> VCFVariantReader::fields()
{

    return parseHeader("INFO");

}
//------------------------------------------------------------------

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
//------------------------------------------------------------------

Variant VCFVariantReader::readVariant()
{
    QString line;
    do
    {
      line = device()->readLine();
    } while (line.startsWith("#"));


   QStringList rows = line.split(QChar::Tabulation);


   QString chrom  = rows[0];
   quint64 pos    = rows[1].toInt();
   QByteArray ref = rows[3].toUtf8();
   QByteArray alt = rows[4].toUtf8();


   Variant variant(chrom,pos, ref,alt);


   return variant;

}
//------------------------------------------------------------------

//Genotype VCFVariantReader::readGenotype()
//{

//}

//------------------------------------------------------------------

QList<Field> VCFVariantReader::parseHeader(const QString &id)
{
    QList<Field> fields;

    if ( device()->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device());
        QString line;

        do
        {
            line = stream.readLine();

            if (line.startsWith(QString("##%1").arg(id)))
            {
                QRegularExpression ex(QString("^##%1=<ID=(.+),Number=(.+),Type=(.+),Description=\"(.+)\".+").arg(id));
                QRegularExpressionMatch match = ex.match(line);

                QString id   = match.captured(1);
                QString desc = match.captured(4);

                // do not save specialID info fields like ANN, SnpEff, VEP...
                // manage them separatly
                if (!mSpecialId.contains(id))
                    fields.append(Field(id, desc));
            }

        } while (line.startsWith("##"));
    }
    device()->close();

    return fields;
}

QList<Field> VCFVariantReader::parseAnnotationFormat()
{
    QList<Field> fields;

    if ( device()->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device());
        QString line;

        do
        {
            line = stream.readLine();


            if (line.startsWith("##INFO=<ID=ANN"))
            {
                QRegularExpression ex("^##INFO=<ID=ANN,Number=(.+),Type=(.+),Description=\"(.+)\".+");
                QRegularExpressionMatch match = ex.match(line);

                if (!match.hasMatch())
                    qDebug()<<Q_FUNC_INFO<<"no match ANN";

                QString desc = match.captured(3);

                //"Functional annotations: 'Allele | Annotation | Annotation_Impact | Gene_Name | Gene_ID | Feature_Type | Feature_ID | Transcript_BioType | Rank | HGVS.c | HGVS.p | cDNA.pos / cDNA.length | CDS.pos / CDS.length | AA.pos / AA.length | Distance | ERRORS / WARNINGS / INFO' "
                ex.setPattern("\'(.+)\'");
                match = ex.match(desc);

                if (!match.hasMatch())
                    qDebug()<<Q_FUNC_INFO<<"no match ANN fields";

                QStringList items = match.captured(1).split('|');

                // Field name looks like : ANN_1, ANN_2 ....

                for (int i=0; i<items.length(); ++i)
                    fields.append(Field(QString("ANN_%1").arg(i), items.at(i)));
                break;
            }

        } while (line.startsWith("##"));
    }
    device()->close();

    return fields;
}
//------------------------------------------------------------------

}
