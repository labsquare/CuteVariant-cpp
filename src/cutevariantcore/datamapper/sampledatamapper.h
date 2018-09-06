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
    virtual bool insert(const Sample& record) const override;
    virtual bool update(const Sample& record) const override;
    virtual bool remove(const Sample& record) const override;
    virtual Sample fromSql(const QSqlRecord& record) const override;

    virtual bool createTable()const override;

};


}


#endif // SAMPLEDATAMAPPER_H
