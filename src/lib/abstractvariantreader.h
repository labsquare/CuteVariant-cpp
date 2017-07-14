#ifndef ABSTRACTVARIANTREADER_H
#define ABSTRACTVARIANTREADER_H
#include <QtCore>
#include "field.h"
#include "variant.h"
#include "genotype.h"

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
    virtual QStringList samples() const = 0;


    virtual Variant readVariant() = 0;
    virtual Genotype readGenotype() = 0;



private:
    QString mFilename;


};

#endif // ABSTRACTVARIANTREADER_H
