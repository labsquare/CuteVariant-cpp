#ifndef SAMPLE_H
#define SAMPLE_H
#include "resource.h"

class Sample : Resource
{
public:
    Sample();
    Sample(const QString& name);
    QVariant phenotype(const QString& key);


private:
    QString mName;
    QHash<QString, QVariant> mPhenotype;
};

#endif // SAMPLE_H
