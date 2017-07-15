#ifndef VCFVARIANTREADER_H
#define VCFVARIANTREADER_H
#include "abstractvariantreader.h"

class VCFVariantReader : public AbstractVariantReader
{
public:
    VCFVariantReader(const QString& filename);

    /*!
     * \brief extract fields
     * \return Field list object
     */
    virtual QList<Field> fields() const override;

    /*!
     * \brief extract samples
     * \return Samples list name
     */
    virtual QList<Sample> samples() const override;


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
    virtual bool readGenotype(Genotype& variant) override;



};

#endif // VCFVARIANTREADER_H
