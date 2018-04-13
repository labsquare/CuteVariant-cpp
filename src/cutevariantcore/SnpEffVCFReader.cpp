#include "SnpEffVCFReader.h"

namespace cvar {
SnpEffVCFReader::SnpEffVCFReader(const QString &filename)
    :GenericVCFReader(filename)
{

}

SnpEffVCFReader::SnpEffVCFReader(QIODevice *device)
    :GenericVCFReader(device)
{

}

void SnpEffVCFReader::parseAnnotation(const QString line)
{







}


}
