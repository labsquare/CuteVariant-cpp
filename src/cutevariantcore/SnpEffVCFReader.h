#ifndef SNPEFFVCFREADER_H
#define SNPEFFVCFREADER_H
#include <QtCore>
#include "genericvcfreader.h"

namespace cvar {

class SnpEffVCFReader : public GenericVCFReader
{
public:
    SnpEffVCFReader(const QString& filename);
    SnpEffVCFReader(QIODevice *device);



protected:
    void parseAnnotation(const QString line);
};
}

#endif // SNPEFFVCFREADER_H
