#ifndef SAMPLE_H
#define SAMPLE_H
#include "resource.h"
namespace core {
class Sample : Resource
{
public:
    Sample();
    Sample(const QString& name);
    QVariant phenotype(const QString& key);

    const QString& name() const;

    void setName(const QString& name);


private:
    QString mName;
    QHash<QString, QVariant> mPhenotype;
};
}
#endif // SAMPLE_H
