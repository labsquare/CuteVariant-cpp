#ifndef VARIANT_H
#define VARIANT_H
#include <QtCore>

class Variation
{
public:
    Variation();
    Variation(const QString& chromosom,
            quint64 position,
            const QString& ref,
            const QString& alt,
            quint64 quality = 0,
            QString filter = QString());



    const QString &chromosom() const;
    quint64 position() const;
    const QString &identifier() const;
    const QString &ref() const;
    const QString &alt() const;
    quint64 quality() const;
    const QString &filter() const;

    void clearAnnotation();
    void addAnnotation(const QString& key, const QVariant& value);
    const QPair<QString, QVariant>& annotation(int index)const;
    int annotationCount() const;

private:
    QString mChromosom;
    quint64 mPosition = 0;
    QString mIdentifier;
    QString mRef;
    QString mAlt;
    quint64 mQuality = 0;
    QString mFilter;
    QList<QPair<QString, QVariant>> mAnnotations;

};

#endif // VARIANT_H
