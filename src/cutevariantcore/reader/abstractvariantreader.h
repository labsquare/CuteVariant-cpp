#ifndef ABSTRACTVARIANTREADER_H
#define ABSTRACTVARIANTREADER_H
#include <QtCore>
#include "field.h"
#include "variant.h"
#include "sample.h"


/*!
 * Base class for all variants file readers ( VCF, txt ...)
 */





namespace  cvar {

class AbstractVariantReader
{
public:
    AbstractVariantReader(QIODevice * device);


    /*!
     * \brief extract fields
     * \return Field list object
     */
    virtual QList<Field> fields() = 0;

    /*!
     * \brief extract fields
     * \return Field list object
     */
   // virtual QList<Field> genotypeFields() = 0;


    /*!
     * \brief extract samples
     * \return Samples list name
     */
    virtual QList<Sample> samples() = 0;


    /*!
     * \brief readVariant
     * \param use it in a while loop : while (readVariant)...
     * \return true if it reach the end of the line
     */
    virtual Variant readVariant() = 0;


    /*!
     * \brief readGenotype
     * \param use it in a while loop : while (readGenotype)...
     * \return true if it reach the end of the line
     */
    //virtual Genotype readGenotype() = 0;


    virtual QHash<QString, QVariant> metadatas() const {return QHash<QString, QVariant>();}






    //virtual bool open();
    //virtual void close();
   // bool atEnd();

    QIODevice * device() const;




private:
    QIODevice * mDevice;



};


}
#endif // ABSTRACTVARIANTREADER_H
