#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QtSql>
#include <QtConcurrent>
#include "kcompressiondevice.h"
#include "reader/abstractvariantreader.h"
#include "variantreaderfactory.h"

#include "variantdatamapper.h"
#include "regiondatamapper.h"
#include "sampledatamapper.h"
#include "fielddatamapper.h"

namespace cvar {
class Importer : public QObject
{
    Q_OBJECT
public:
    explicit Importer(QObject *parent = nullptr);

    /*!
     * \brief importFile
     * Import any support file into sql database. Do it synchronously
     * \param filename
     * \return true if success
     */
    bool import(const QString& filename, VariantReaderFactory::Format format = VariantReaderFactory::Unknown);

    /*!
     * \brief importFile
     * Import any support file into sql database. Do it asynchronously
     * \param filename
     * \return a QFutur to monitor the progression
     */
    QFuture<bool> asyncImport(const QString& filename, VariantReaderFactory::Format format = VariantReaderFactory::Unknown);



Q_SIGNALS:
    void importRangeChanged(int min, int max);
    void importProgressChanged(int progress, const QString& message = QString());


protected:
    void writeProject(const QString& name);

    void writeFileInfo(const QString& filename);
    void writeBed();
    void writeMetadatas(AbstractVariantReader * reader);
    void writeSamples(AbstractVariantReader * reader);
    void writeFields(AbstractVariantReader * reader);
    void writeVariants(AbstractVariantReader * reader);



private:
    qint64 mFileSize;
    QIODevice * mProgressDevice;

    QHash<QString, QVector<int>> mVariantIds;
    QHash<QString, int> mSamplesIds;

};
}
#endif // IMPORTER_H
