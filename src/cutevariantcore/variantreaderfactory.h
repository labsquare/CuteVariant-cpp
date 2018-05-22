#ifndef VARIANTREADERFACTORY_H
#define VARIANTREADERFACTORY_H
#include <QtCore>
#include "abstractvariantreader.h"
#include "genericvcfreader.h"

namespace cvar {
class VariantReaderFactory
{
public :

    static AbstractVariantReader * createVariantReader(const QString& filename);



    static bool isVcf(QIODevice * device);
    static bool isSnpEff(QIODevice * device);
    static bool isVep(QIODevice * device);
    static bool isAnnovar(QIODevice * device);



private:
    VariantReaderFactory();






};

}
#endif // VARIANTREADERFACTORY_H
