#include "sampledatamapper.h"

namespace cvar {

SampleDataMapper::SampleDataMapper()
    :DataMapper<Sample, SampleDataMapper>("samples")
{

}

bool cvar::SampleDataMapper::insert(const cvar::Sample &record)
{

    qDebug()<<"ya";

}


void cvar::SampleDataMapper::createTable()
{
        qDebug()<<"create table";
}

bool cvar::SampleDataMapper::update(const Sample &record)
{

}

bool cvar::SampleDataMapper::remove(const Sample &record)
{

}



Sample SampleDataMapper::get(int id) const
{

}

QList<Sample> SampleDataMapper::list() const
{

}

}
