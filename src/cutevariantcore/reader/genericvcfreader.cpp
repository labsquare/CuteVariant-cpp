#include "genericvcfreader.h"
namespace cvar {

GenericVCFReader::GenericVCFReader(QIODevice *device)
    :AbstractVariantReader(device)
{
    mSamples = samples();
}

GenericVCFReader::~GenericVCFReader()
{

}
//------------------------------------------------------------------
QList<Field> GenericVCFReader::fields()
{
    QList<Field> fields;

    fields.append(Field::standardField(Field::Chromosom));
    fields.append(Field::standardField(Field::Position));
    fields.append(Field::standardField(Field::Reference));
    fields.append(Field::standardField(Field::Alternative));

    fields.append(Field("QUAL","variants","quality", QVariant::Int));
    fields.append(Field("FILTER","variants","filter", QVariant::String));
    fields.append(Field("RSID","variants","dbSnp ID ", QVariant::String));

    // add samples as fields

    auto genotypes =  parseHeader(QStringLiteral("FORMAT"));

    for (const Sample& s : mSamples)
    {
        for (const Field& f : genotypes)
            fields.append(Field(s.name()+"_"+f.name(),"samples",f.description(), f.type()));

    }

    // add annotation as fields

    for (Field& f : parseHeader(QStringLiteral("INFO")))
    {

        if (mAnnParser.keys().contains(f.name()))
            fields.append(mAnnParser[f.name()]->parseFields(f));

        else {
            f.setName("INFO_"+f.name());
            fields.append(f);

        }
    }

    return fields;
}

//------------------------------------------------------------------
//QList<Field> GenericVCFReader::genotypeFields()
//{
//    return parseHeader(QStringLiteral("FORMAT"));
//}
//------------------------------------------------------------------

QList<Sample> GenericVCFReader::samples()
{
    QList<Sample> samples;

    if (device()->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device());

        while (!stream.atEnd())
        {
            // detect the following pattern :
            // #CHROM	POS	ID	REF	ALT	QUAL	FILTER	INFO	FORMAT	BLANK	NA12878	NA12891	NA12892	NA19238	NA19239	NA19240

            QString line = stream.readLine();
            if (line.startsWith(QStringLiteral("#CHROM")))
            {
                QStringList header = line.split(QChar::Tabulation);
                if (header.size() > 9)
                {
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
QHash<QString, quint64> GenericVCFReader::contigs()
{
    QHash<QString, quint64> contigList;

    // detect the following pattern
    // ##contig=<ID=20,length=62435964,assembly=B36,md5=f126cdf8a6e0c7f379d618ff66beb2da,species="Homo sapiens",taxonomy=x>

    if ( device()->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device());

        while (!stream.atEnd())
        {
            QString line = stream.readLine().toLower();
            if (line.startsWith(QStringLiteral("##contig")))
            {
                QRegularExpression exp("##contig=<id=(.+),length=(\\d+)");
                exp.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
                QRegularExpressionMatch match = exp.match(line);

                if (match.hasMatch())
                {
                    QString chr    = match.captured(1);
                    quint64 length = match.captured(2).toInt();

                    contigList.insert(chr.toLower(),length);
                }

            }
        }
    }
    device()->close();
    return contigList;
}
//------------------------------------------------------------------
Variant GenericVCFReader::readVariant()
{
    if (!mVariantBuffer.isEmpty())
        return mVariantBuffer.takeLast();

    QString line;

    do {

        line = device()->readLine();

    } while (line.startsWith("#"));



    Variant variant = parseVariant(line);

    // create duplicate variant per annotation
    for (const QString& key : mAnnParser.keys())
    {
        // ex : ANN=C|...
        if (variant.annotations().contains("INFO_"+key)){
            auto variants = mAnnParser[key]->parseVariant(variant);
            mVariantBuffer.append(variants);
        }

    }

    if (mVariantBuffer.isEmpty())
        mVariantBuffer.append(variant);

    return mVariantBuffer.takeLast();

}
//------------------------------------------------------------------

Variant GenericVCFReader::parseVariant(const QString& line)
{
    if (line.isEmpty())
        return Variant();

    QStringList rows = line.split('\t');
    if ( rows.size() < 8)
    {
        qCritical()<<"Wrong fields number in file";
        return Variant();
    }

    QString chrom  = rows[0];
    quint64 pos    = quint64(rows[1].toInt());
    QString ref    = rows[3];
    QString alt    = rows[4];

    QString rsid   = rows[2];
    QString qual   = rows[5];
    QString filter = rows[6];
    QString info   = rows[7];

    Variant variant(chrom,pos, ref,alt);
    //    variant.setRsId(rsid);
    //    variant.setQual(qual.toDouble());
    //    variant.setFilter(filter);
    variant.setBin(Variant::maxUcscBin(pos-1, pos));

    variant.addAnnotation("VARIANTS_QUAL", qual);
    variant.addAnnotation("VARIANTS_FILTER", filter);
    variant.addAnnotation("VARIANTS_RSID", rsid);


    // parse samples format
    if (rows.size() > 8)
    {
        QStringList formats = rows[8].split(":");

        for (int i=9; i<rows.size(); ++i)
        {

            QString sample     = mSamples.at(i-9).name();
            QStringList values = rows[i].split(":");

            for (int j=0; j<formats.size(); j++)
            {
                QString colname = QString("SAMPLES_%1_%2").arg(sample, formats[j]);
                variant.addAnnotation(colname, values[j]);

            }



        }
    }




    // parse annotation info
    for (QString item : info.split(";"))
    {
        if (item.contains("="))
        {
            QStringList pair = item.split("=");
            QString key      = pair.first();
            QString val      = pair.last();
            QString colname  = "INFO_" + key.toUpper();
            variant[colname] = val;
        }
        // Bool TAGS
        else
        {
            // If key is present, means it's true
            // by default it's false
            variant[item] = 1;
        }
    }

    return variant;

}

//Genotype GenericVCFReader::readGenotype()
//{
//    if (mGenotypesOfCurrentLine.isEmpty())
//    {
//        mGenotypesOfCurrentLine = readGenotypeLine(device()->readLine());
//        return mGenotypesOfCurrentLine.takeFirst();
//    }

//    return mGenotypesOfCurrentLine.takeFirst();
//}


//QList<Genotype> GenericVCFReader::readGenotypeLine(const QString &line)
//{
//    // return all genotypes find on one line

//    QStringList rows = line.split(QChar::Tabulation);
//    if (rows.size() < 10)
//    {
//        qCritical()<<"Cannot read genotype. Wrong fields count";
//        return QList<Genotype>();
//    }

//    QString chrom  = rows[0];
//    quint64 pos    = rows[1].toInt();
//    QString ref    = rows[3];
//    QString alt    = rows[4];

//    // FORMAT field
//    QStringList cols = rows[8].split(":");

//    // Loop over all sample Genotype FIELDS
//    QList<Genotype> genotypes;

//    for (int i=0; i<mSamples.size(); ++i)
//    {
//        QStringList vals = rows[9+i].split(":");

//        if (cols.length() != vals.length())
//            qCritical()<<Q_FUNC_INFO<<"genotypes fields and values have different sizes";

//        // save genotype annotation
//        Genotype gen  =  Genotype(chrom,pos,ref,alt,mSamples[i].name());

//        for (int i=0; i<qMin(cols.length(), vals.length()); ++i)
//            gen.addAnnotation(cols[i], vals[i]);

//        genotypes.append(gen);
//    }

//    return genotypes;
//}

//bool GenericVCFReader::open()
//{
//    // Get samples to process genotype later
//    mSamples = samples();

//    // get contigs if exists
//    mContigs = contigs();

//    if (!AbstractVariantReader::open())
//        return false;

//    device()->reset();

//    // Avoid comment when reading by seeking in the file
//    QString line;
//    int lastPos = 0;
//    do
//    {
//        lastPos = device()->pos();
//        line = device()->readLine();
//    } while (line.startsWith("#"));

//    device()->seek(lastPos);

//    return true;
//}

GenericVCFReader::Format GenericVCFReader::format() const
{

    if (metadatas().keys().contains("VEP"))
        return Format::VEP;

    if (metadatas().keys().contains("SnpEffVersion") || metadatas().keys().contains("snpeffversion"))
        return Format::SNPEFF;

    return Format::Generic;
}

void GenericVCFReader::addAnnotationParser(AbstractAnnotationParser *parser)
{
    mAnnParser.insert(parser->label(), parser);
}
//------------------------------------------------------------------

QList<Field> GenericVCFReader::parseHeader(const QString &id)
{
    // Get all Fields started with ##ID
    // For instance
    // ##INFO=<ID=DP,Number=1,Type=Integer,Description="Total Depth">
    // ##INFO=<ID=AF,Number=.,Type=Float,Description="Allele Frequency">

    QList<Field> fields;

    if (device()->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device());
        QString line;

        do
        {
            line = stream.readLine();

            // Parse Header line
            if (line.startsWith(QString("##%1").arg(id)))
            {
                QRegularExpression ex(QStringLiteral("^##%1=<ID=(.+),Number=(.+),Type=(.+),Description=\"(.+)\".+").arg(id));
                QRegularExpressionMatch match = ex.match(line);

                QString name   = match.captured(1);
                QString type   = match.captured(3);
                QString desc   = match.captured(4);

                QVariant::Type fType = QVariant::String;

                if (type == "String" || type == "Character")
                    fType = QVariant::String;

                if (type == "Integer")
                    fType = QVariant::Int;

                if (type == "Float")
                    fType = QVariant::Double;

                if (type == "Flag")
                    fType = QVariant::Bool;

                fields.append(Field(name,id,desc, fType));

            }

        } while (line.startsWith("##"));
    }

    device()->close();

    return fields;
}


//------------------------------------------------------------------
QHash<QString, QVariant> GenericVCFReader::metadatas() const
{
    QHash<QString, QVariant> meta;

    QStringList ignoreKey = {"INFO","FORMAT","FILTER"};

    if ( device()->open(QIODevice::ReadOnly))
    {
        QTextStream stream(device());
        QString line;
        do
        {
            line = stream.readLine();
            // Parse Header line
            if (line.startsWith("##"))
            {
                QRegularExpression ex(QStringLiteral("^##(?<key>[^=]+)=(?<value>[^<]+)"));
                ex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
                QRegularExpressionMatch match = ex.match(line);

                QString key     = match.captured("key").toLower().simplified();
                QVariant val    = match.captured("value").simplified();

                if (!ignoreKey.contains(key.toUpper()))
                {
                    if (!key.isEmpty())
                        meta[key] = val;

                }
            }

        } while (line.startsWith("##"));
    }

    device()->close();

    return meta;
}




}
