#ifndef VCFIMPORTER_H
#define VCFIMPORTER_H
#include <QtCore>
#include <QtSql>
#include "field.h"

class SubParser;
class AnnSubParser;
class VcfImporter;

class SubParser
{
public:
    virtual void parseHeader(const QString& desc) = 0;
    virtual QString identifer() = 0;
    QList<Field> fields() const;

protected:
    void addField(const Field& field);
    void setValue(const QString& fieldName, const QVariant& value);

private:
    QHash<QString,Field> mHeaders;
    QHash<QString,QVariant> mValues;

};

class AnnSubParser: public SubParser
{
public :
    void parseHeader(const QString &line) Q_DECL_OVERRIDE;
    QString identifer() {return "ANN";}
};

class DefaultParser : public SubParser
{
public:
    void parseHeader(const QString &line) Q_DECL_OVERRIDE;
    QString identifer() {return "DEFAULT";}

};

class VcfImporter : public QThread
{
public:
    VcfImporter(QObject * parent = Q_NULLPTR);
    void setFileNames(const QStringList& paths);

    void run() Q_DECL_OVERRIDE;


    int insertVariant(const QString& chrom, quint64 pos, const QString& ref, const QString& alt);
    int insertSample(const QString& sample, int fileID);
    int insertFilename(const QFile &file);
    int insertAnnotation(int variantID, const QHash<QString, QVariant>& annotations);

    void createAnnotationTable();


    QList<Field> parseInfoHeader(const QString& line);
    QList<QVariant> parseInfo(const QString& info);




protected:
    QStringList tableColumnNames(const QString& tableName) const;


private:
    QStringList mPaths;
    QList<Field> mInfoFields;
    QList<Field> mFormatFields;
    bool mHeaderParsed = false;

    QSqlQuery mVariantQuery;


    QHash<QString, SubParser*> mSubParsers;

};

#endif // VCFIMPORTER_H
