#include "queryobserver.h"

QueryObserver::QueryObserver(QObject * parent)
    :QObject (parent)
{

}

void QueryObserver::addObservable(AbstractQueryWidget *widget)
{
    mWidgets.append(widget);

}

const cvar::VariantQuery &QueryObserver::query()
{
    for (auto * w : mWidgets)
    {
        w->readQuery(mQuery);
    }

    return mQuery;
}

void QueryObserver::setQuery(const cvar::VariantQuery &query)
{
    mQuery = query;

    for (auto * w : mWidgets)
    {
        w->writeQuery(mQuery);
    }



}
