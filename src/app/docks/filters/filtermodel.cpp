#include "filtermodel.h"
#include <QDebug>


//============================================
FilterModel::FilterModel(QObject * parent)
    :QStandardItemModel(parent)
{
    appendRow(new LogicItem("AND"));


}

void FilterModel::addLogic(LogicItem *item, QStandardItem *parent)
{
    if (parent == nullptr){
        //appendRow(item);
        // disable append root. Keep only one tree root
    }
    else
        parent->appendRow(item);
}

void FilterModel::addCondition(FilterItem *item, QStandardItem *parent)
{
    parent->appendRow(item);
}

QString FilterModel::makeQuery()
{

    QString out = recursiveQuery(item(0,0));

    if (out == "()")
        return QString();

    return out;


}

QString FilterModel::recursiveQuery(QStandardItem *item)
{

    if (item->rowCount() == 0)
        return "("+item->data(FilterItem::ConditionRole).toString()+")";

    QStringList list;
    for (int i = 0; i< item->rowCount(); ++i)
    {
        list.append(" "+recursiveQuery(item->child(i))+" ");

    }

    qDebug()<<list;

    QString out ;

    if (item->text() =="AND")
        out = list.join("AND");

    if (item->text() =="OR")
        out = list.join("OR");



    return "("+out+")";


}

QVariant FilterModel::data(const QModelIndex &index, int role) const
{
    return QStandardItemModel::data(index,role);
}




