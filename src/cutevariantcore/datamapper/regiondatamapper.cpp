#include "regiondatamapper.h"

namespace cvar{

RegionDataMapper::RegionDataMapper()
    :DataMapper<Region, RegionDataMapper>("regions")
{
    addColumn("chr", DataColumn::Text, "NOT NULL");
    addColumn("start", DataColumn::Integer, "NOT NULL");
    addColumn("end", DataColumn::Integer, "NOT NULL");

}


QHash<QString, QVariant> RegionDataMapper::write(const Region &record) const
{
    return {
        {"chr", record.chromosom()},
        {"start", record.start()},
        {"end", record.end()}
    };
}

Region RegionDataMapper::read(const QSqlRecord &record) const
{
    Region region;

    region.setChromosom(record.value("chr").toString());
    region.setStart(record.value("start").toInt());
    region.setEnd(record.value("end").toInt());

    return region;

}

}
