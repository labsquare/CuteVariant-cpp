#include "vcfvariantreader.h"
namespace core {
VCFVariantReader::VCFVariantReader(const QString &filename)
    :AbstractVariantReader(filename)
{

    // Get Header Fields data, to process variant later
    // Store map between fields name in the VCF and colname in sqlite
    for (Field f : fields())
        mFieldColMap[f.name()] = f.colname();

    // Get samples to process genotype later
    mSamples = samples();


}
//------------------------------------------------------------------
QList<Field> VCFVariantReader::fields()
{
    return parseHeader(QStringLiteral("INFO"));
}

QList<Field> VCFVariantReader::genotypeFields()
{
    return parseHeader(QStringLiteral("FORMAT"));
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

Variant VCFVariantReader::readVariant()
{
    // return dupliate variant before processing next line
    if (!mDuplicateVariant.isEmpty())
    {
        return mDuplicateVariant.takeLast();
    }


    QString line = device()->readLine();
    QStringList rows = line.split('\t');
    if ( rows.size() < 8)
    {
        qCritical()<<"Wrong fields number in file";
        return Variant();
    }
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

            //
            // Do not manage special key like ANN
            //
            if (mSpecialId.contains(key))
            {
                QStringList allAnn = val.split(",");

                // Save first annotation as usual
                int index = 0;
                for (QString annValue : allAnn.first().split("|")){
                    variant[mSpecialIdMap[key].value(index)] = annValue;
                    ++index;
                }

                // save duplicate variant if many annotations for this variant
                if (allAnn.size() > 1)
                {
                    mDuplicateVariant.clear();
                    for (int dupId = 1; dupId<allAnn.size(); ++dupId)
                    {
                        Variant dupVariant = variant;
                        int index = 0;
                        for (QString annValue : allAnn[dupId].split("|")){
                            dupVariant[mSpecialIdMap[key].value(index)] = annValue;
                            ++index;
                        }
                        mDuplicateVariant.append(dupVariant);
                    }
                }
            }

            // normal info fields
            else
            {
                variant[mFieldColMap[key]] = val;
            }
        }

        // Bool TAGS
        else
        {
            // If key is present, means it's true
            variant[mFieldColMap[item]] = 1;
        }

    }
    return variant;
}

Genotype VCFVariantReader::readGenotype()
{
    // read after all sample has been process ...
    if (mCurrentSampleId == 0)
        mCurrentGenotypeLine = device()->readLine();

    QStringList rows = mCurrentGenotypeLine.split(QChar::Tabulation);

    if (rows.size() < 10)
    {
        qCritical()<<"Cannot read genotype. Wrong fields count";
        return Genotype();
    }

    QString chrom  = rows[0];
    quint64 pos    = rows[1].toInt();
    QString ref    = rows[3];
    QString alt    = rows[4];

    QStringList cols = rows[8].split(":");
    QStringList vals = rows[9+mCurrentSampleId].split(":");

    Genotype gen =  Genotype(chrom,pos,ref,alt,mSamples[mCurrentSampleId].name());

    if (cols.length() != vals.length())
        qCritical()<<Q_FUNC_INFO<<"genotypes fields and values have different sizes";

    // save genotype annotation
    for (int i=0; i<qMin(cols.length(), vals.length()); ++i)
    {
        if (cols[i] == QStringLiteral("GT"))
            gen.setRawGenotype(vals[i]);
        else
            gen.addAnnotation(cols[i], vals[i]);
    }

    // read next line for the next call
    if (mCurrentSampleId < mSamples.count() - 1)
        mCurrentSampleId ++;
    else
        mCurrentSampleId = 0;

    return gen;

}

bool VCFVariantReader::open()
{
    if (!AbstractVariantReader::open())
        return false;

    // Avoid comment when reading
    QString line;
    do
    {
        line = device()->readLine();
    } while (line.startsWith("#"));


    return true;
}
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
            // Parse Header line
            if (line.startsWith(QString("##%1").arg(id)))
            {
                QRegularExpression ex(QStringLiteral("^##%1=<ID=(.+),Number=(.+),Type=(.+),Description=\"(.+)\".+").arg(id));
                QRegularExpressionMatch match = ex.match(line);

                QString name   = match.captured(1);
                QString type   = match.captured(3);
                QString desc   = match.captured(4);

                if (mSpecialId.contains(name)){
                    fields += parseAnnotationHeaderLine(line);
                }

                else
                {

                    Field::Type fType = Field::TEXT;

                    if (type == "String" || type == "Character")
                        fType = Field::TEXT;

                    if (type == "Integer")
                        fType = Field::INTEGER;

                    if (type == "Float")
                        fType = Field::REAL;

                    if (type == "Flag")
                        fType = Field::BOOL;

                    fields.append(Field("INFO_"+name, name, desc, fType));
                }

            }

        } while (line.startsWith("##"));
    }

    device()->close();

    return fields;
}

QList<Field> VCFVariantReader::parseAnnotationHeaderLine(const QString& line)
{

    // typical annotation are in the following form. Many fields in one line
    //##INFO=<ID=CSQ,Number=.,Type=String,Description="Consequence annotations from Ensembl VEP. Format: Allele|Consequence|IMPACT|SYMBOL|Gene|Feature_type|Feature|BIOTYPE|EXON|INTRON|HGVSc|HGVSp|cDNA_position|CDS_position|Protein_position|Amino_acids|Codons|Existing_variation|DISTANCE|STRAND|FLAGS|SYMBOL_SOURCE|HGNC_ID|TSL|APPRIS|SIFT|PolyPhen|AF|AFR_AF|AMR_AF|EAS_AF|EUR_AF|SAS_AF|AA_AF|EA_AF|ExAC_AF|ExAC_Adj_AF|ExAC_AFR_AF|ExAC_AMR_AF|ExAC_EAS_AF|ExAC_FIN_AF|ExAC_NFE_AF|ExAC_OTH_AF|ExAC_SAS_AF|CLIN_SIG|SOMATIC|PHENO|PUBMED|MOTIF_NAME|MOTIF_POS|HIGH_INF_POS|MOTIF_SCORE_CHANGE|MetaSVM_pred|MetaSVM_score">

    QList<Field> fields;


    QRegularExpression ex(QStringLiteral("^##INFO=<ID=(?<id>.+),Number=(?<number>.+),Type=(?<type>.+),Description=\"(?<desc>.+):(?<ann>.+)\""));
    QRegularExpressionMatch match = ex.match(line);

    if (match.hasMatch())
    {
        QString id   = match.captured("id");
        QString ann  = match.captured("ann");
        // remove quote if exists.. ( snpEFF )
        ann = ann.remove("\'");
        ann = ann.remove("\"");
        ann = ann.simplified();
        ann = ann.remove(QChar::Space);

        for (QString a : ann.split("|"))
        {
            fields.append(Field(id+"_"+a,a,"See Annotation specification"));
            mSpecialIdMap[id].append(fields.last().colname());
        }
    }


    return fields;
}
//------------------------------------------------------------------

}
