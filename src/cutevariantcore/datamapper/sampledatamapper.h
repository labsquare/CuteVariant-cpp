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
    virtual bool insert(const Sample& record) override;

    virtual bool update(const Sample& record) override;
    virtual bool remove(const Sample& record) override ;



    virtual Sample get(int id) const override;
    virtual QList<Sample> list() const override;

    virtual void createTable();
};


}


#endif // SAMPLEDATAMAPPER_H
