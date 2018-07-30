#ifndef VARIANTREADERFACTORY_H
#define VARIANTREADERFACTORY_H
#include <QtCore>
#include "reader/abstractvariantreader.h"
#include "reader/genericvcfreader.h"

namespace cvar {
class VariantReaderFactory : QObject
{
    Q_OBJECT
public :

    enum Format
    {
        Unknown,
        Vcf,
        SnpEff,
        Vep,
        Annovar,
        Tabular

    };

    Q_ENUM(Format)


    static AbstractVariantReader * createVariantReader(const QString& filename);

    static Format fileFormat(const QString& filename);



    static bool isVcf(QIODevice * device);
    static bool isSnpEff(QIODevice * device);
    static bool isVep(QIODevice * device);
    static bool isAnnovar(QIODevice * device);



private:
    VariantReaderFactory();






};

}
#endif // VARIANTREADERFACTORY_H
