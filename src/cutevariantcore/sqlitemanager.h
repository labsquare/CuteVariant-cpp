#ifndef VARIANTIMPORTER_H
#define VARIANTIMPORTER_H
#include <QSqlDatabase>
#include <QtSql>
#include <QObject>
#include <QtGui>
#include <QtConcurrent>
#include "reader/abstractvariantreader.h"
#include "reader/genericvcfreader.h"
#include "variantquery.h"
#include "view.h"
#include "variantlink.h"
#include "region.h"
#include "bedfile.h"
#include "variantreaderfactory.h"
#include "kcompressiondevice.h"

namespace cvar {

/*!
 * \brief The SqliteManager class
 * This is the interface between raw SQLITE query and C++ POO
 */
class Project;
class VariantQuery;
class SqliteManager : public QObject
{
    Q_OBJECT
public:
    enum CompareMode {
        SiteMode ,
        VariantMode
    };
    SqliteManager(QObject * parent = 0);
    ~SqliteManager();

    /*!
     * \brief createProject
     * Create sqlite file with default table
     * \param name
     */
    void createProject(const QString& name);

    /*!
     * \brief samples
     * \return samples list from sqlite
     */
    QList<Sample> samples() const;

    /*!
     * \brief regions
     * \param bedId
     * \return regions from a specific bed file id
     */
    QList<Region> regions(int bedId) const;

    QList<BedFile> bedFiles() const;

    /*!
     * \brief fields
     * \return variant fields from sqlite
     */
    QList<Field> fields() const;
    /*!
     * \brief genotypeFields
     * \return genotype field from sqlite
     */
    QList<Field> genotypeFields(const Sample& sample) const;

    /*!
     * \brief metadatas
     * In VCF file, metadata correspond to header data as key value.
     * \return metadata from input file
     */
    QHash<QString, QVariant> metadatas() const;

    /*!
     * \brief variantSets
     * A variant set is a sql view of variants. You can see it as a sql table of variant
     * \return return all variant sets
     */
    QList<View> variantSets() const;

    /*!
     * \brief variantSetName
     * \return return names of collections
     */
    QStringList variantSetNames() const;

    bool removeVariantSet(const QString& setName);

    /*!
     * \brief createVariantSetFromExpression
     * This methods create a new variant set from other set using operator.
     * ex : newSet = SetA - SetB .
     * \param newSet : the name of new variant set
     * \param expression : a Set expression with set operator. (+ - & )
     * \param mode how to perform set operation
     * \return true if success
     */
    bool createVariantSetFromExpression(const QString& newSetName, const QString& expression, CompareMode mode = SiteMode);

    /*!
     * \brief createVariantSet
     * \param query
     * \param setName
     * \param description
     * \return
     */
    bool createVariantSet(const VariantQuery& query, const QString& setName, const QString& description = QString());

    /*!
     * \brief variants
     * \param query
     * \return return raw Sql Query from a Variant Query object
     */
    QSqlQuery variants(const VariantQuery & query) const;

    /*!
     * \brief variantsCount
     * \param query
     * \return how many variant for a specific VariantQuery
     */
    int variantsCount(const VariantQuery& query) ;



    QHash<QString,int> variantsStats(const VariantQuery& query) const;


    /*!
     * \brief variantsCount
     * \param table
     * \return how many variant from a specific set
     */
    int variantsCount(const QString& setName = "variants");

    /*!
     * \brief variant
     * \param variantId
     * \return a Variant from sql ID
     */
    Variant variant(int variantId) const;

    /*!
     * \brief importFile
     * Import any support file into sql database. Do it synchronously
     * \param filename
     * \return true if success
     */
    bool importFile(const QString& filename, VariantReaderFactory::Format format = VariantReaderFactory::Unknown);

    /*!
     * \brief importFile
     * Import any support file into sql database. Do it asynchronously
     * \param filename
     * \return a QFutur to monitor the progression
     */
    QFuture<bool> asyncImportFile(const QString& filename, VariantReaderFactory::Format format = VariantReaderFactory::Unknown);


    bool importBedfile(const QString& filename);



protected:
    void createFile(const QString& filename);
    void createBed();
    void createMetadatas(AbstractVariantReader * reader);
    void createSample(AbstractVariantReader * reader);
    void createFields(AbstractVariantReader * reader);
    void createGenotypeFields(AbstractVariantReader * reader);
    void createVariants(AbstractVariantReader * reader);
    void createGenotypes(AbstractVariantReader * reader);


    static QByteArray md5sum(const QString& filename);
    static QByteArray iconToData(const QIcon& icon);


Q_SIGNALS:
    void importRangeChanged(int min, int max);
    void importProgressChanged(int progress, const QString& message = QString());

private:
    QHash<QString, QVector<int>> mVariantIds;
    QHash<QString, int> mSamplesIds;

    QIODevice * mProgressDevice;
    quint64 mFileSize;


};

}
#endif // VARIANTIMPORTER_H
