#ifndef SAMPLEDATAMAPPER_H
#define SAMPLEDATAMAPPER_H
#include <QtSql>
#include "datamapper.h"
#include "sample.h"

namespace cvar {

class SampleDataMapper : public DataMapper<Sample, SampleDataMapper>
{
public:
    SampleDataMapper();

    virtual QHash<QString, QVariant> write(const Sample& record) const override ;
    virtual Sample read(const QSqlRecord& record) const override;

};


}


#endif // SAMPLEDATAMAPPER_H
