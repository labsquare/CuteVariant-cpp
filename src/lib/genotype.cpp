#include "genotype.h"
namespace core {

Genotype::Genotype()
    :Resource()
{

}

Genotype::Genotype(const Variant &variant, const Sample &sample)
{
  mVariant = variant;
  mSample  = sample;

}
}

