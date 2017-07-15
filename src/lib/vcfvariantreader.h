#ifndef VCFVARIANTREADER_H
#define VCFVARIANTREADER_H
#include "abstractvariantreader.h"
#include "vcfreader.h"
#include "field.h"
namespace core {

class VCFVariantReader : public AbstractVariantReader
{
public:
    VCFVariantReader(const QString& filename);

    /*!
     * \brief extract fields
     * \return Field list object
     */
    virtual QList<Field> fields() override;

    /*!
     * \brief extract samples
     * \return Samples list name
     */
    virtual QList<Sample> samples() override;


    /*!
     * \brief readVariant
     * \param use it in a while loop : while (readVariant)...
     * \return true if it reach the end of the line
     */
    virtual bool readVariant(Variant& variant) override;
    /*!
     * \brief readGenotype
     * \param use it in a while loop : while (readGenotype)...
     * \return true if it reach the end of the line
     */
    virtual bool readGenotype(Genotype& genotype) override;



protected:
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

    /*!
     * \brief parse Vep Annotation from ANN specification
     * exemple :
     * http://snpeff.sourceforge.net/VCFannotationformat_v1.0.pdf
     * ##INFO=<ID=ANN,Number=.,Type=String,Description="Functional annotations: 'Allele | Annotation | Annotation_Impact | Gene_Name | Gene_ID | Feature_Type | Feature_ID | Transcript_BioType | Rank | HGVS.c | HGVS.p | cDNA.pos / cDNA.length | CDS.pos / CDS.length | AA.pos / AA.length | Distance | ERRORS / WARNINGS / INFO' ">
     * \param id
     * \return
     */
    QList<Field> parseAnnotationFormat();


private:
    // special INFO field id like ANN, SnpEff..
    // dot not manage them
    const QStringList mSpecialId = {"ANN"};



};
}

#endif // VCFVARIANTREADER_H
