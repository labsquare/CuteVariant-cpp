#ifndef VCFVARIANTREADER_H
#define VCFVARIANTREADER_H
#include "abstractvariantreader.h"
#include "vcfreader.h"
#include "field.h"
#include "abstractannotationparser.h"
#include "vepannotationparser.h"
#include "snpeffannotationparser.h"


namespace cvar {

class GenericVCFReader : public AbstractVariantReader
{
public:
    enum Format {
        VEP,
        SNPEFF,
        Generic,
    };

    GenericVCFReader(const QString& filename);
    GenericVCFReader(QIODevice *device);


    /*!
     * \brief extract fields
     * \return Field list object
     */
    virtual QList<Field> fields() override;

    /*!
     * \brief extract fields
     * \return Field list object
     */
    virtual QList<Field> genotypeFields() override;


    /*!
     * \brief extract samples
     * \return Samples list name
     */
    virtual QList<Sample> samples() override;


     QHash<QString, quint64> contigs();

    /*!
     * \brief readVariant
     * \param use it in a while loop : while (readVariant)...
     * \return true if it reach the end of the line
     */
    virtual Variant readVariant() override;


    /*!
     * \brief readVariant
     * \param use it in a while loop : while (readGenotype)...
     * \return true if it reach the end of the line
     */
    virtual Genotype readGenotype() override;

    virtual bool open() override;

     Format format() const;






    //protected:
    /*!
     * \brief parse Vcf Header according ID.
     * For exemple, with id equal 'INFO', 3 fields will be extract:
     * ##INFO=<ID=AA,Number=1,Type=String,Description="Ancestral Allele">
     * ##INFO=<ID=DB,Number=0,Type=Flag,Description="dbSNP membership, build 129">
     * ##INFO=<ID=H2,Number=0,Type=Flag,Description="HapMap2 membership">
     * \param id
     * \return
     */
    QList<Field> parseHeader(const QString& id);
    Variant parseVariant(const QString & line);


    QList<Genotype> readGenotypeLine(const QString& line);


    /*!
     * \brief parse Annotation from ANN specification
     * exemple : // Get Header Fields data, to process variant later
    // Store map between fields name in the VCF and colname in sqlite
    for (Field f : fields())
        mFieldColMap[f.name()] = f.colname();

    // Get samples to process genotype later
    mSamples = samples();
     * http://snpeff.sourceforge.net/VCFannotationformat_v1.0.pdf
     * ##INFO=<ID=ANN,Number=.,Type=String,Description="Functional annotations: 'Allele | Annotation | Annotation_Impact | Gene_Name | Gene_ID | Feature_Type | Feature_ID | Transcript_BioType | Rank | HGVS.c | HGVS.p | cDNA.pos / cDNA.length | CDS.pos / CDS.length | AA.pos / AA.length | Distance | ERRORS / WARNINGS / INFO' ">
     * \param id
     * \return
     */


    /*!
     * \brief metas
     * return file meta data key value
     * \return
     */
    QHash<QString, QVariant> metadatas() const;






private:
    // special INFO field id like ANN, SnpEff..
    // dot not manage them


   // QHash<QString, QStringList> mSpecialIdMap;


    // need to store fields header before read variant

    QList<Sample> mSamples;
    QHash<QString, quint64> mContigs;

    QList<Genotype> mGenotypesOfCurrentLine;

    // used to to generate Genotype per sample in genotype read parser


    QList<Variant> mVariantBuffer;


    // One Line can have multiple annotation
    // We decide to store one annotation by row in variant table.
    // That's means duplicate variant with different annotation
//    QList<Variant> mDuplicateVariant;



    QList<AbstractAnnotationParser*> mAnnParser = {

        new VepAnnotationParser(),
        new SnpEffAnnotationParser()


    };



};
}

#endif // VCFVARIANTREADER_H
