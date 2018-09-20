#ifndef REGIONDATAMAPPER_H
#define REGIONDATAMAPPER_H
#include "datamapper.h"
#include "region.h"
namespace cvar {
class RegionDataMapper : public DataMapper<Region, RegionDataMapper>
{
public:
    RegionDataMapper();

    virtual QHash<QString, QVariant> toSql(const Region& record) const final;
    virtual Region fromSql(const QSqlRecord& record) const final;

    void importBed(const QString& filename) const;

};

}
#endif // REGIONDATAMAPPER_H
