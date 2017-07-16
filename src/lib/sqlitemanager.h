#ifndef VARIANTIMPORTER_H
#define VARIANTIMPORTER_H
#include <QSqlDatabase>
#include <QtSql>
#include "abstractvariantreader.h"
#include "vcfvariantreader.h"

namespace core {

/*!
 * \brief The SqliteManager class
 * This is the interface between raw SQLITE query and C++ POO
 */
class SqliteManager
{
public:
    SqliteManager();
    void createProject(const QString& name);
    bool importFile(const QString& filename);



protected:
    void createSample(AbstractVariantReader * reader);
    void createFields(AbstractVariantReader * reader);
    void createVariants(AbstractVariantReader * reader);




private:

};

}
#endif // VARIANTIMPORTER_H
