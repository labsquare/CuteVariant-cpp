#ifndef VARIANTIMPORTER_H
#define VARIANTIMPORTER_H
#include <QSqlDatabase>
#include <QtSql>
#include "abstractvariantreader.h"
#include "vcfvariantreader.h"
#include "variantquery.h"

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

    /*!
     * \brief variants
     * \param query
     * select variants from database
     * \return
     */
    QList<Variant> variants(const VariantQuery& query);

    /*!
     * \brief variantsCount
     * \param query
     * Return variants count
     * \return
     */
    int variantsCount(const VariantQuery& query);

    /*!
     * \brief variantsTo
     * \param query
     * \param taget
     * Save variant selection into target
     * \return
     */
    bool variantsTo(const VariantQuery& query, const QString& target);


    QList<Sample> samples() const;
    QStringList samplesNames() const;




protected:
    void createSample(AbstractVariantReader * reader);
    void createFields(AbstractVariantReader * reader);
    void createVariants(AbstractVariantReader * reader);
    void createGenotypes(AbstractVariantReader * reader);




private:
    QHash<QString, QVector<int>> mVariantIds;
    QHash<QString, int> mSamplesIds;

};

}
#endif // VARIANTIMPORTER_H
