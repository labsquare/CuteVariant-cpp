#include "filterdelegate.h"
#include "filterwidget.h"

FilterDelegate::FilterDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{


}

QWidget * FilterDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{



//    const FilterModel * m = qobject_cast<const FilterModel*>(index.model());

//    if (m->itemFromIndex(index)->type() == FilterModel::LogicType)
//    {
//        QComboBox * box = new QComboBox(parent);
//        box->setFrame(false);
//        box->addItems({"AND","OR"});
//        return box;

//    }



    return QStyledItemDelegate::createEditor(parent, option, index);
}

void FilterDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //const FilterModel * m = qobject_cast<const FilterModel*>(index.model());

//    if (m->itemFromIndex(index)->type() == FilterModel::LogicType)
//    {
//        QFont font = painter->font();
//        font.setBold(true);
//        painter->setFont(font);
//        painter->drawText(option.rect, Qt::AlignLeft, index.data().toString());
//        return;

//    }





    return QStyledItemDelegate::paint(painter, option, index);
}
