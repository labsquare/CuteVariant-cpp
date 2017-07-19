#include "vcfvariantreader.h"
namespace core {
VCFVariantReader::VCFVariantReader(const QString &filename)
    :AbstractVariantReader(filename)
{

    // Get Header Fields data, to process variant later
    // Store map between fields name in the VCF and colname in sqlite
    for (Field f : fields())
        mFieldColMap[f.name()] = f.colname();


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
    QString rsid   = rows[2];
    QString ref    = rows[3];
    QString alt    = rows[4];
    QString qual   = rows[5];
    QString filter = rows[6];
    QString info   = rows[7];

    Variant variant(chrom,pos, ref,alt);
    variant.setRsId(rsid);
    variant.setQual(qual.toDouble());
    variant.setFilter(filter);

    // pre-fill annotation . Usefull for Flag values. Missing key means False
    for (QString colnames : mFieldColMap.values())
        variant.addAnnotation(colnames, 0);

    // parse annotation info
    for (QString item : info.split(";"))
    {
        if (item.contains("="))
        {
            QStringList pair = item.split("=");
            QString key = pair.first();
            QString val = pair.last();

            // Do not manage special key like ANN
            if (!mSpecialId.contains(key))
                variant[mFieldColMap[key]] = val;
        }

        else
        {
            // If key is present, means it's true
            variant[mFieldColMap[item]] = 1;
        }


    }




    return variant;

}
//------------------------------------------------------------------

//Genotype VCFVariantReader::readGenotype()
//{

//}toInt();

//------------------------------------------------------------------

QList<Field> VCFVariantReader::parseHeader(const QString &id)
{
    QList<Field> fields;
    int annotation_index = 1 ; // Annotation number index

    if ( device()->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device());
        QString line;

        do
        {
            line = stream.readLine();

            // Parse Header line
            if (line.startsWith(QString("##%1").arg(id)))
            {
                QRegularExpression ex(QString("^##%1=<ID=(.+),Number=(.+),Type=(.+),Description=\"(.+)\".+").arg(id));
                QRegularExpressionMatch match = ex.match(line);

                QString name   = match.captured(1);
                QString type   = match.captured(3);
                QString desc   = match.captured(4);

                // parse Fields info line
                // do not save specialID info fields like ANN, SnpEff, VEP...
                // manage them separatly
                if (!mSpecialId.contains(id)){
                    QString colname = QString("%1_%2").arg(id).arg(annotation_index);

                    Field::Type fType = Field::TEXT;

                    if (type == "String" || type == "Character")
                        fType = Field::TEXT;

                    if (type == "Integer")
                        fType = Field::INTEGER;

                    if (type == "Float")
                        fType = Field::REAL;

                    if (type == "Flag")
                        fType = Field::BOOL;


                    fields.append(Field(colname, name, desc, fType));

                    ++annotation_index;
                }
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
