#ifndef GENOTYPE_H
#define GENOTYPE_H
#include "resource.h"
#include "variant.h"
#include "sample.h"
namespace core {
class Genotype : public Resource
{
public:
    Genotype();
    Genotype(const Variant& variant, const Sample& sample);


private:
    Variant mVariant;
    Sample mSample;


};
}

#endif // GENOTYPE_H
