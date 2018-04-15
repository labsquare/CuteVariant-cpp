#include "chartdockwidget.h"

ChartDockWidget::ChartDockWidget(QWidget *parent)
    :BaseDockWidget()
{

    setTitle("Plots");


    mView  = new QChartView;
    chart  = new QChart();
    series = new QPieSeries();

    mView->setRenderHint(QPainter::Antialiasing);

    mView->setChart(chart);


    setWidget(mView);


}

void ChartDockWidget::setQuery(const cvar::VariantQuery &query)
{
    // Not compute is not visible
    if (!isVisible())
        return ;


    series->clear();




    QHash<QString,int> statsHash = cutevariant->sqlite()->variantsStats(query);
    auto i = statsHash.begin();
    for (i = statsHash.begin(); i != statsHash.end(); ++i){
        series->append(i.key(), i.value());
    }


    for (auto &slice : series->slices())
    {
        slice->setLabelVisible(true);
        slice->setLabel(slice->label().split("",QString::SkipEmptyParts).join(">"));
    }

    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addSeries(series);
    chart->setTitle("Snp count");
    chart->legend()->hide();




}
