#ifndef VCFIMPORTER_H
#define VCFIMPORTER_H
#include <QtCore>
#include <QtSql>
#include "field.h"

class VcfImporter : public QThread
{
public:
    VcfImporter(QObject * parent = Q_NULLPTR);
    void setFileNames(const QStringList& paths);
    void run() Q_DECL_OVERRIDE;

    int insertVariant(const QString& chrom, quint64 pos, const QString& ref, const QString& alt);
    int insertSample(const QString& sample, int fileID);
    int insertFilename(const QFile &file);
    int insertAnnotation(int variantID, int fieldID, const QVariant& value);

    void insertFields(QList<Field>& fields);


    // parse variant annotations header specification ANN
    QList<Field> parseHeader_ANN(const QString& description);

    Field infoField(const QString& name) const;


private:
    QStringList mPaths;
    QList<Field> mInfoFields;
    QList<Field> mFormatFields;

    bool mHeaderParsed = false;

    QSqlQuery mVariantQuery;


};

#endif // VCFIMPORTER_H
