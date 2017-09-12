#ifndef VARIANTIMPORTER_H
#define VARIANTIMPORTER_H
#include <QSqlDatabase>
#include <QtSql>
#include <QObject>
#include <QtConcurrent>
#include "abstractvariantreader.h"
#include "vcfvariantreader.h"
#include "variantquery.h"
#include "selection.h"

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
    SqliteManager(QObject * parent = 0);
    ~SqliteManager();
    void createProject(const QString& name);

    QList<Sample> samples() const;
    QList<Field> fields() const;
    QList<Field> genotypeFields() const;
    QList<Field> genotype(const Sample& sample) const;
    QList<VariantSelection> variantSelections();
    bool removeSelection(const QString& name);


    QSqlQuery variants(const VariantQuery & query) const;
    int variantsCount(const VariantQuery& query) const;
    bool variantsTo(const VariantQuery& query, const QString& tablename, const QString& description = QString());


    Variant variant(int variantId) const;

    QFuture<bool> asyncImportFile(const QString& filename);
    bool importFile(const QString& filename);


protected:
    void createFile(const QString& filename);
    void createSample(AbstractVariantReader * reader);
    void createFields(AbstractVariantReader * reader);
    void createGenotypeFields(AbstractVariantReader * reader);
    void createVariants(AbstractVariantReader * reader);
    void createGenotypes(AbstractVariantReader * reader);

    static QByteArray md5sum(const QString& filename);


Q_SIGNALS:
    void importRangeChanged(int min, int max);
    void importProgressChanged(int progress, const QString& message = QString());

private:
    QHash<QString, QVector<int>> mVariantIds;
    QHash<QString, int> mSamplesIds;


};

}
#endif // VARIANTIMPORTER_H
