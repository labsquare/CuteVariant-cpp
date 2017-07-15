#include "vcfvariantreader.h"

VCFVariantReader::VCFVariantReader(const QString &filename)
    :AbstractVariantReader(filename)
{

}

QList<Field> VCFVariantReader::fields() const
{

}

QList<Sample> VCFVariantReader::samples() const
{

}

bool VCFVariantReader::readVariant(Variant &variant)
{

}

bool VCFVariantReader::readGenotype(Genotype &variant)
{

}
