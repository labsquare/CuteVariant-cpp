#ifndef VARIANTIMPORTER_H
#define VARIANTIMPORTER_H
#include <QSqlDatabase>
#include <QtSql>
#include <QObject>
#include <QtGui>
#include <QtConcurrent>
#include "abstractvariantreader.h"
#include "vcfvariantreader.h"
#include "variantquery.h"
#include "selection.h"
#include "variantlink.h"

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
    void createProject(const QString& name);

    // getter
    QList<Sample> samples() const;
    QList<Field> fields() const;
    QList<Field> genotypeFields(const Sample& sample) const;
    QList<VariantLink> links() const;
    QList<VariantSelection> variantSelections() const; //TODO rename better
    QStringList variantSelectionNames() const;

    bool createSelectionFromExpression(const QString& newtable, const QString& rawExpression, CompareMode mode = SiteMode);


    // saver
    bool saveLink(VariantLink& link);

    // deleter
    bool removeSelection(const QString& name);
    bool removeLink(const VariantLink& link);


    QSqlQuery variants(const VariantQuery & query) const;
    int variantsCount(const VariantQuery& query) const;
    bool variantsTo(const VariantQuery& query, const QString& tablename, const QString& description = QString());


    Variant variant(int variantId) const;

    QFuture<bool> asyncImportFile(const QString& filename);
    bool importFile(const QString& filename);


protected:
    void createFile(const QString& filename);
    void createLinks();
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


};

}
#endif // VARIANTIMPORTER_H
