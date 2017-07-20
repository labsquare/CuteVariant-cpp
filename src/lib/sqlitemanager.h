#ifndef VARIANTIMPORTER_H
#define VARIANTIMPORTER_H
#include <QSqlDatabase>
#include <QtSql>
#include "abstractvariantreader.h"
#include "vcfvariantreader.h"
#include "querybuilder.h"

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

    QList<Sample> samples() const;
    QStringList samplesNames() const;

    QString queryToSql(const QString& raw);






protected:
    void createSample(AbstractVariantReader * reader);
    void createFields(AbstractVariantReader * reader);
    void createVariants(AbstractVariantReader * reader);
    void createGenotypes(AbstractVariantReader * reader);




private:
    QHash<QString, QVector<int>> mVariantIds;
    QHash<QString, int> mSamplesIds;

    QueryBuilder mQueryBuilder;


};

}
#endif // VARIANTIMPORTER_H
