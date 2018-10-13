#include "selectionmodel.h"

SelectionModel::SelectionModel(QObject *parent)
{

}

void SelectionModel::load()
{
 clear();
 setColumnCount(2);

 for (cvar::View &v : cvar::ViewDataMapper::i()->list())
 {

       QStandardItem * nameItem = new QStandardItem;
       nameItem->setText(v.name());

       QStandardItem * countItem = new QStandardItem;
       countItem->setText(QString::number(v.count()));

       appendRow({nameItem, countItem});

 }



}
