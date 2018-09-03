#ifndef SAMPLE_H
#define SAMPLE_H
#include <QtCore>

namespace cvar {
class Sample;
class Sample
{
public:
    Sample(const QString& name = QString());
    QVariant phenotype(const QString& key);

    const QString& name() const;
    void setName(const QString& name);


private:
    QString mName;
    QHash<QString, QVariant> mPhenotype;
};
}
#endif // SAMPLE_H
