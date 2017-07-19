#ifndef GENOTYPE_H
#define GENOTYPE_H
#include <QtCore>
#include "resource.h"
#include "variant.h"
#include "sample.h"
namespace core {
class Genotype : public Resource
{
public:
    enum Type {
        Double_alt = -1,
        Homozygous_ref = 0,
        Heterozygous = 1,
        Homozygous_alt = 2
    };
    Genotype();
    Genotype (const QString& chr,
              quint64 pos,
              const QString& ref,
              const QString& alt,
              const QString& sampleName,
              const QString& rawGenotype);


    Genotype::Type type() const;
    QString typeName() const;

    bool isHomo() const;
    bool isHetero() const;

private:
    Variant mVariant;
    Sample mSample;
    QString mRawGenotype;




};
}

#endif // GENOTYPE_H
