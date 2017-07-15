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


private:
    Variant mVariant;
    Sample mSample;


};
}

#endif // GENOTYPE_H
