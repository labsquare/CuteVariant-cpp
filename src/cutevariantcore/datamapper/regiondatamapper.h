#ifndef REGIONDATAMAPPER_H
#define REGIONDATAMAPPER_H
#include "datamapper.h"
#include "region.h"
namespace cvar {
class RegionDataMapper : public DataMapper<Region, RegionDataMapper>
{
public:
    RegionDataMapper();

    virtual QHash<QString, QVariant> write(const Region& record) const final;
    virtual Region read(const QSqlRecord& record) const final;

};

}
#endif // REGIONDATAMAPPER_H
