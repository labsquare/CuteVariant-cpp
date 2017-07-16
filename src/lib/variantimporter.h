#ifndef VARIANTIMPORTER_H
#define VARIANTIMPORTER_H
#include <QSqlDatabase>
#include <QtSql>
#include "abstractvariantreader.h"
#include "vcfvariantreader.h"

namespace core {

class VariantImporter
{
public:
    VariantImporter();
    bool importFile(const QString& filename);


protected:
    void createSample(AbstractVariantReader * reader);
    void createFields(AbstractVariantReader * reader);
    void createVariants(AbstractVariantReader * reader);

    void createShema();



private:

};

}
#endif // VARIANTIMPORTER_H
