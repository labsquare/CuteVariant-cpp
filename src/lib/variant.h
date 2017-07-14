#ifndef VARIANT_H
#define VARIANT_H
#include <QtCore>
#include "resource.h"

class Variant : public Resource
{
public:
    Variant();
    Variant(const QString& chr, quint64 pos, QByteArray& ref, QByteArray& alt);

private:
    QString mChr;
    quint64 mPos;
    QByteArray mRef;
    QByteArray mAlt;
};

#endif // VARIANT_H
