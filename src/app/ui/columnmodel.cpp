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
    commonItem->setCheckable(true);


    // add annotation
    QStandardItem * annItem = new QStandardItem;
    annItem->setText("annotation");
    annItem->setCheckable(true);

    for (core::Field f : mProject->sqliteManager()->fields())
    {

        QStandardItem * c1 = new QStandardItem;
        c1->setText(f.colname());
        c1->setToolTip(f.description());
        c1->setCheckable(true);


        annItem->appendRow(c1);
    }

    appendRow(annItem);



    // add Samples
    QStandardItem * sampleItem = new QStandardItem;
    sampleItem->setText("samples");
    sampleItem->setCheckable(true);


    for (core::Sample s : mProject->sqliteManager()->samples())
    {

        QStandardItem * c1 = new QStandardItem;
        c1->setText(s.name());
        sampleItem->appendRow(c1);
        c1->setCheckable(true);


        for (core::Field f : mProject->sqliteManager()->genotypeFields())
        {
            QStandardItem * g = new QStandardItem(f.name());
            g->setToolTip(f.description());
            g->setCheckable(true);
            c1->appendRow(g);
        }
    }

    appendRow(sampleItem);


}
