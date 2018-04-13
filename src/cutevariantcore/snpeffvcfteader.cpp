#include "snpeffvcfteader.h"

namespace cvar {
SnpEffVCFReader::SnpEffVCFReader(const QString &filename)
    :GenericVCFReader(filename)
{

}

SnpEffVCFReader::SnpEffVCFReader(QIODevice *device)
    :GenericVCFReader(device)
{

}

QList<Field> SnpEffVCFReader::fields()
{
    QList<Field> f = GenericVCFReader::fields() ;

    f.append(Field("ANN_GENE","GENE","The gene affected by the variant",Field::TEXT));
    f.append(Field("ANN_TRANSCRIPT","GENE","The transcript affected by the variant", Field::TEXT));
    f.append(Field("ANN_IS_EXONIC","IS_EXONIC","Does the variant affect an exon for this transcript?", Field::BOOL));
    f.append(Field("ANN_IS_CODING","IS_CODING","Does the variant fall in a coding region", Field::BOOL));
    f.append(Field("ANN_IS_LOF","IS_LOF","Based on the value of the impact col, is the variant LOF", Field::BOOL));
    f.append(Field("ANN_EXON","EXON","Exon information for the variants that are exonic", Field::TEXT));
    f.append(Field("ANN_CODON_CHANGE","CODON_CHANGE","What is the codon change", Field::TEXT));
    f.append(Field("ANN_AA_CHANGE","AA_CHANGE","What is the amino acid change?", Field::TEXT));
    f.append(Field("ANN_AA_LENGTH","AA_LENGTH","The length of CDS in terms of number of amino acids ?", Field::TEXT));
    f.append(Field("ANN_BIOTYPE","BIOTYPE","The type of transcript (e.g., protein-coding, pseudogene, rRNA etc.", Field::TEXT));
    f.append(Field("ANN_IMPACT","IMPACT","mpacts due to variation ", Field::TEXT));
    f.append(Field("ANN_IMPACT_SO","IMPACT_SO","The sequence ontology term for the impact", Field::TEXT));
    f.append(Field("ANN_IMPACT_SEVERITY","IMPACT_SEVERITY","Severity of the impact based on the impact column value (ref.impact category)", Field::TEXT));

    return f;


}

Variant SnpEffVCFReader::readVariant()
{

    if (mDuplicateVariantsPerAnnotation.isEmpty())
    {
        mDuplicateVariantsPerAnnotation = parseVariantAnnotation(GenericVCFReader::readVariant());
        return mDuplicateVariantsPerAnnotation.takeFirst();
    }

    return mDuplicateVariantsPerAnnotation.takeFirst();
}

QVector<Variant> SnpEffVCFReader::parseVariantAnnotation(const Variant &variant)
{

    // if no annotation, do as usual
    if (!variant.annotations().keys().contains("INFO_ANN"))
        return { variant };


    // Loop over this ...
    // ANN=T|missense_variant|MODERATE|CCT8L2|ENSG00000198445|transcript|ENST00000359963|protein_coding|1/1|c.1406G>A|p.Gly469Glu|1666/2034|1406/1674|469/557||,
    //T|downstream_gene_variant|MODIFIER|FABP5P11|ENSG00000240122|transcript|ENST00000430910|processed_pseudogene||n.*397G>A|||||3944|

    QVector<Variant> variants;
    for (QString raw : variant.annotation("INFO_ANN").toString().split(","))
    {
        QStringList elements = raw.split("|");
        Variant annVariant   = variant;
        annVariant.removeAnnotation("INFO_ANN");

        if (elements.size() < 12) // TODO 13 ?
        {
            qCritical()<<Q_FUNC_INFO<<"Wrong annotation field number";
            return variants;
        }

        QString alt         = elements[0];
        QString effect      = elements[1];
        QString impact      = elements[2];
        QString gene_name   = elements[3];
        //QString gene_id   = elements[4];
        //QString feature_type = elements[5];
        QString feature_id   = elements[6];
        QString biotype      = elements[7];
        //QString rank         = elements[8];
        QString codonChange  = elements[9];
        QString aaChange     = elements[10];

        QString cdnaPosRaw   = elements[11];
        QString cdsPosRaw    = elements[12];

        int cdnaPos    = -1;
        int cdnaLength = -1;
        int cdsPos     = -1;
        int cdsLength  = -1;

        //        cDNA_position / cDNA_len: Position in cDNA and trancript’s cDNA length (one based).
        //        CDS_position / CDS_len: Position and number of coding bases (one based includes START and STOP codons).

        // TODO optimize [] instead at()
        if (cdnaPosRaw.contains(QRegularExpression("\\d+\/\\d+"))){
            cdnaPos    = cdnaPosRaw.split("/").at(0).toInt();
            cdnaLength = cdsPosRaw.split("/").at(1).toInt();
        }

        if (cdsPosRaw.contains(QRegularExpression("\\d+\/\\d+"))){
            cdsPos    = cdsPosRaw.split("/").at(0).toInt();
            cdsLength = cdsPosRaw.split("/").at(1).toInt();
        }

        // cdn position ./ cdna length
        // protein position / protein len

        annVariant.setAlt(alt);
        annVariant.addAnnotation("ANN_GENE",gene_name );
        annVariant.addAnnotation("ANN_TRANSCRIPT",feature_id );
        annVariant.addAnnotation("ANN_IS_EXONIC", cdnaPos > 0 );
        annVariant.addAnnotation("ANN_IS_CODING", cdsPos > 0 );
        annVariant.addAnnotation("ANN_IS_LOF", "NA");
        annVariant.addAnnotation("ANN_EXON", "NA");
        annVariant.addAnnotation("ANN_CODON_CHANGE", codonChange);
        annVariant.addAnnotation("ANN_AA_CHANGE", aaChange);
        annVariant.addAnnotation("ANN_AA_LENGTH", cdsLength);
        annVariant.addAnnotation("ANN_BIOTYPE", biotype);

        annVariant.addAnnotation("ANN_IMPACT", impact);
        annVariant.addAnnotation("ANN_IMPACT_SO", effect);
        annVariant.addAnnotation("ANN_IMPACT_SEVERITY", effect);



        variants.append(annVariant);



    }
    return variants;
}

}
