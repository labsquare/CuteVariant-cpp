#include "columnmodel.h"

ColumnModel::ColumnModel(core::Project *prj, QObject *parent)
    :QStandardItemModel(parent), mProject(prj)
{

    load();

}

void ColumnModel::load()
{
    setColumnCount(1);


    // add common
    QStandardItem * commonItem = new QStandardItem;
    commonItem->setText("variant");

    commonItem->appendRow(new QStandardItem("chr"));
    commonItem->appendRow(new QStandardItem("pos"));
    commonItem->appendRow(new QStandardItem("ref"));
    commonItem->appendRow(new QStandardItem("alt"));
    commonItem->appendRow(new QStandardItem("qual"));
    commonItem->appendRow(new QStandardItem("filter"));

    appendRow(commonItem);



    // add annotation
    QStandardItem * annItem = new QStandardItem;
    annItem->setText("annotation");

    for (core::Field f : mProject->sqliteManager()->fields())
    {

        QStandardItem * c1 = new QStandardItem;
        c1->setText(f.colname());
        c1->setToolTip(f.description());


        annItem->appendRow(c1);
    }

    appendRow(annItem);



    // add Samples
    QStandardItem * sampleItem = new QStandardItem;
    sampleItem->setText("samples");

    for (core::Sample s : mProject->sqliteManager()->samples())
    {

        QStandardItem * c1 = new QStandardItem;
        c1->setText(s.name());
        sampleItem->appendRow(c1);
    }

    appendRow(sampleItem);


}
