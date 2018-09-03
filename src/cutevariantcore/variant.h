#ifndef VARIANT_H
#define VARIANT_H
#include <QtCore>
#include "abstractrecord.h"
namespace cvar{
class Variant;
class Variant : public AbstractRecord
{
public:
    Variant(const QString& chr = QString(), quint64 pos = 0, const QString& ref = QString(), const QString& alt = QString());
    void addAnnotation(const QString& colname, const QVariant& value);
    void clearAnnotation();
    void removeAnnotation(const QString& colname);
    QVariant annotation(const QString& colname) const;
    QVariant& operator[] (const QString& colname);
    bool operator==(const Variant &v1);


    void setChr(const QString& chr);
    void setPos(quint64 pos);
    void setRef(const QString& ref);
    void setAlt(const QString& alt);
    void setRsId(const QString& rsid);
    void setFilter(const QString& filter);
    void setQual(double qual);

    bool isNull() const;

   QString name() const;
   QString coordinate() const;
   QString igvUrl() const;
   QString varsomeUrl() const;


    const QString& chromosom() const;
    quint64 position() const;
    const QString& ref() const;
    const QString& alt() const;
    const QString& rsId() const;
    const QString& filter() const;
    double qual() const;


    quint64 bin() const;
    void setBin(quint64 bin);

//    static int binFromRangeStandard(int start, int end);
//    static int binFromRangeExtended(int start, int end);

    static QList<int> ucscBins(int start, int end);
    static int maxUcscBin(int start, int end);


    QHash<QString, QVariant> annotations() const;

    const QString& comment() const;
    void setComment(const QString &comment);

    bool isFavoris() const;
    void setFavoris(bool isFavoris);

    int score() const;
    void setScore(int score);


    // virtual methods
    virtual bool update() override;
    virtual bool insert() override;
    virtual bool remove() override;

    virtual void fromSql(const QSqlRecord& record) override;

    // static methods
    static void createTable();



private:
    quint64 mBin = 0;
    QString mChr;
    quint64 mPos;
    QString mRef;
    QString mAlt;
    QString mRsId;
    QString mFilter;
    double mQual = 0;
    QString mComment;
    int mScore = 0;
    bool mIsFavoris = false;


    QHash<QString,QVariant> mAnnotations;
};
}
#endif // VARIANT_H
