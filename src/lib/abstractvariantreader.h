#ifndef ABSTRACTVARIANTREADER_H
#define ABSTRACTVARIANTREADER_H
#include <QtCore>
#include "field.h"
#include "variant.h"
#include "genotype.h"
#include "sample.h"

class AbstractVariantReader
{
public:
    AbstractVariantReader(const QString& filename);

    /*!
     * \brief extract fields
     * \return Field list object
     */
    virtual QList<Field> fields() const = 0;

    /*!
     * \brief extract samples
     * \return Samples list name
     */
    virtual QList<Sample> samples() const = 0;


    /*!
     * \brief readVariant
     * \param use it in a while loop : while (readVariant)...
     * \return true if it reach the end of the line
     */
    virtual bool readVariant(Variant& variant) = 0;
    /*!
     * \brief readGenotype
     * \param use it in a while loop : while (readGenotype)...
     * \return true if it reach the end of the line
     */
    virtual bool readGenotype(Genotype& variant) = 0;



    const QString& filename() const;

protected:
    QIODevice * device();




private:
    QIODevice * mDevice;
    QString mFilename;


};

#endif // ABSTRACTVARIANTREADER_H
