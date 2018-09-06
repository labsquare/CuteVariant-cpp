#include "sampledatamapper.h"
#include "sample.h"
namespace cvar {

SampleDataMapper::SampleDataMapper()
    :DataMapper<Sample, SampleDataMapper>("samples")
{

}

bool SampleDataMapper::insert(const Sample &record) const
{
    return sqlInsert({
                         {"name" , record.name()}
                     });


}

bool SampleDataMapper::update(const Sample &record) const
{
    return sqlUpdate({
                         {"id", record.id()},
                         {"name" , record.name()}
                     });
}

bool SampleDataMapper::remove(const Sample &record) const
{
    return sqlRemove(record.id());
}

Sample SampleDataMapper::fromSql(const QSqlRecord &record) const
{

    Sample sample;
    sample.setId(record.value("id").toInt());
    sample.setName(record.value("name").toString());

    return sample;
}

bool SampleDataMapper::createTable() const
{

    return sqlCreateTable({
                              {"name", "TEXT NOT NULL"}
                          });
}



}
