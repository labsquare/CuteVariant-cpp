#ifndef QUERYOBSERVER_H
#define QUERYOBSERVER_H
#include <QObject>
#include "variantquery.h"
#include "abstractquerywidget.h"

class QueryObserver : public QObject
{
public:
    QueryObserver(QObject * parent = nullptr);
    void addObservable(AbstractQueryWidget * widget);

    const cvar::VariantQuery& query();
    void setQuery(const cvar::VariantQuery& query);

private:
    QList<AbstractQueryWidget*> mWidgets;

    cvar::VariantQuery mQuery;


};

#endif // QUERYOBSERVER_H
