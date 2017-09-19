#ifndef VARIANT_H
#define VARIANT_H
#include <QtCore>
#include "resource.h"
namespace cvar{
class Variant : public Resource
{
public:
    Variant();
    Variant(const QString& chr, quint64 pos, QString& ref, QString& alt);
    void addAnnotation(const QString& colname, const QVariant& value);
    void clearAnnotation();
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
    void setBin(const quint64 &bin);

private:
    quint64 mBin = 0;
    QString mChr;
    quint64 mPos;
    QString mRef;
    QString mAlt;
    QString mRsId;
    QString mFilter;
    double mQual;


    QHash<QString,QVariant> mAnnotations;
};
}
#endif // VARIANT_H
