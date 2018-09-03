#ifndef GENOTYPE_H
#define GENOTYPE_H
#include <QtCore>
#include "abstractrecord.h"
#include "variant.h"
#include "sample.h"
namespace cvar {
class Genotype : public AbstractRecord
{
public:
    enum Type {
        Double_alt = -1,
        Homozygous_ref = 0,
        Heterozygous = 1,
        Homozygous_alt = 2
    };
    Genotype (const QString& chr = QString(),
              quint64 pos  = 0,
              const QString& ref = QString(),
              const QString& alt = QString(),
              const QString& sampleName = QString());

    /*!
     * \brief set raw genotype
     * \param raw : For example 0/1 for heterzygous or 0|0 for homozygous
     */
    void setRawGenotype(const QString& raw);
    /*!
     * \brief add annotation to the genotype
     * \param colname
     * \param value
     */
    void addAnnotation(const QString& colname, const QVariant& value);
    void clearAnnotation();
    /*!
     * \brief annotationNames
     * \return annotation columns names
     */
    QStringList annotationNames() const;
    /*!
     * \brief get annotation from colname
     * \param colname
     * \return annotation value
     */
    QVariant annotation(const QString& colname) const;
    QVariant& operator[](const QString& colname);


    /*!
     * \brief type of genotype
     * \return homozygous or heterozygous
     */
    Genotype::Type type() const;
    QString typeName() const;

    bool isHomo() const;
    bool isHetero() const;

    bool isNull() const;

    /*!
     * \brief sample
     * \return the sample associated with this genotype
     */
    const Sample& sample() const;
    /*!
     * \brief variant
     * \return the variant associated with this genotype
     */
    const Variant& variant() const;

    /*!
     * \brief rawGenotype
     * \return genotype in format "0/1"
     */
    QString rawGenotype() const;


    // virtual methods
    virtual bool update() override;
    virtual bool insert() override;
    virtual bool remove() override;

    virtual void fromSql(const QSqlRecord& record) override;

    // static methods
    static void createTable();



private:
    Variant mVariant;
    Sample mSample;
    QString mRawGenotype;

    QHash<QString,QVariant> mAnnotations;





};
}

#endif // GENOTYPE_H
