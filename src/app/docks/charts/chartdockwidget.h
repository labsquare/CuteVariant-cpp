#ifndef CHARTDOCKWIDGET_H
#define CHARTDOCKWIDGET_H
#include <QtCharts>
#include <QtConcurrent>
using namespace QtCharts;

#include "basedockwidget.h"
#include "variantquery.h"
#include "cutevariant.h"

class ChartDockWidget : public BaseDockWidget
{
public:
    ChartDockWidget(QWidget * parent = nullptr);

    void setQuery(const cvar::VariantQuery& query);



private:
    QChartView * mView;
    QChart *chart;
    QPieSeries *series;
};

#endif // CHARTDOCKWIDGET_H
