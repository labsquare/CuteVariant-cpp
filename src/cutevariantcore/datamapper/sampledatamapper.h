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
//    virtual bool insert(const QList<Sample>& records) const override;
//    virtual bool update(const Sample& record) const override;
//    virtual bool remove(const Sample &record) const override;
//    virtual bool createTable() const override;
//    virtual Sample fromSql(const QSqlRecord& record) const override;


    virtual QHash<QString, QVariant> bind(const Sample& record) const override ;
    virtual Sample fromSql(const QSqlRecord& record) const override;

};


}


#endif // SAMPLEDATAMAPPER_H
