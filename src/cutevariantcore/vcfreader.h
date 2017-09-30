#ifndef VCFREADER_H
#define VCFREADER_H
#include <QObject>
#include <QtCore>
namespace vcfreader {

class Record;
class Field;
class VcfReader;

class Record
{
public:
    explicit Record();
    explicit Record(const QString& chrom,
                    quint64 pos,
                    const QString& id,
                    const QString& ref,
                    const QStringList& alt,
                    quint64 qual,
                    const QString& filter,
                    const QVariantMap& infos,
                    const QString& format = QString(),
                    const QHash<QString, QVariantMap>& samples = QHash<QString, QVariantMap>());

    const QString& chrom()const {return mChrom;}
    quint64 pos()const {return mPos;}
    const QString id()const {return mId;}
    const QString& ref()const {return mRef;}
    const QStringList& alt()const{ return mAlt; }
    quint64 qual()const { return mQual;}
    const QString& filter()const{return mFilter;}
    const QVariantMap& infos()const{return mInfos;}
    const QString& format()const{ return mFormat;}
    QStringList alleles() const;
    quint64 start() const;
    quint64 end() const;
    bool isSnp() const;


private:
    QString mChrom;
    quint64 mPos  = 0;
    QString mId;
    QString mRef;
    QStringList mAlt;
    quint64 mQual = 0;
    QString mFilter;
    QVariantMap mInfos;
    QHash<QString, QVariantMap> mSamples;
    QString mFormat;




};

class Field
{
public:
    QString id;
    QString type;
    QString description;
    QString number;
    static QVariant::Type typeFromString(const QString& type);

};


class VcfReader : public QObject
{
    Q_OBJECT
public:
    explicit VcfReader(QObject *parent = Q_NULLPTR);
    explicit VcfReader(const QString& filename, QObject * parent = Q_NULLPTR);
    explicit VcfReader(QIODevice * device, QObject * parent = Q_NULLPTR);
    const QHash<QString,Field>& infos() const;
    const QHash<QString,Field>& formats() const;
    const QHash<QString,QVariant>& metadata() const;

    bool open();
    bool next() ;

    const Record& record() const;
    const QStringList& samples() const;
protected:
    void readHeader();
    Record readRecord(const QString& raw);

private:
    QTextStream mStream;
    QIODevice * mDevice;
    QString mFilename;
    QByteArray mHeader;
    QHash<QString, Field> mInfos;
    QHash<QString, Field> mFormats;
    QHash<QString, QVariant> mMetadata;
    QStringList mSamples;
    Record mCurrentRecord;

};
}

#endif // VCFREADER_H
