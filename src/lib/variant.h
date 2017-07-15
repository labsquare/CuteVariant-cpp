#ifndef VARIANT_H
#define VARIANT_H
#include <QtCore>
#include "resource.h"
namespace core{
class Variant : public Resource
{
public:
    Variant();
    Variant(const QString& chr, quint64 pos, QByteArray& ref, QByteArray& alt);
    void addAnnotation(const QString& key, const QVariant& value);
    void clearAnnotation();


private:
    QString mChr;
    quint64 mPos;
    QByteArray mRef;
    QByteArray mAlt;
    QHash<QString, QVariant> mAnnotations;
};
}
#endif // VARIANT_H
