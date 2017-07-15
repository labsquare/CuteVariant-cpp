#ifndef VCFVARIANTREADER_H
#define VCFVARIANTREADER_H
#include "abstractvariantreader.h"
#include "vcfreader.h"
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
    QList<Field> parseHeader(const QString& id);

};
}

#endif // VCFVARIANTREADER_H
