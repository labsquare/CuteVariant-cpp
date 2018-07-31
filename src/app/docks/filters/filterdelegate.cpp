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



    // key
    QFont font  = painter->font();
    QFontMetrics metrics(font);

    QRect bgRect = option.rect;
    bgRect.setWidth(metrics.width(index.data().toString()) + 5);
    bgRect.adjust(0,3,0,-3);


    painter->setRenderHint(QPainter::Antialiasing, true);
    if (index.column() == 0 && index.data(Qt::UserRole).toString() == "logic")
    {
        painter->setPen(QColor("#4E9A06"));
        font.setBold(true);
        painter->setFont(font);
        painter->drawText(option.rect, Qt::AlignLeft|Qt::AlignVCenter,index.data().toString());


    }

    if ( index.data(Qt::UserRole).toString() == "key")
    {
        painter->setBrush(QColor("#e6e6e6"));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(bgRect,5,5);
        painter->setPen(QColor("#4183B0"));
        font.setBold(false);
        painter->setFont(font);
        painter->drawText(bgRect, Qt::AlignCenter|Qt::AlignVCenter, index.data().toString());

        // Draw grip
        QStyleOptionToolBar gripOption;
        gripOption.rect = QRect(0,option.rect.y(),option.rect.height(), option.rect.height());
        gripOption.toolBarArea = Qt::TopToolBarArea;
        gripOption.rect.setX(-10);
        //qApp->style()->drawControl(QStyle::CE_Splitter,&gripOption, painter);

       // qApp->style()->drawPrimitive(QStyle::PE_IndicatorToolBarHandle,&gripOption,painter);




    }

    if (index.data(Qt::UserRole).toString() == "operator" ) // Operator
    {
        painter->setPen(QColor("#EA9F37"));
        font.setBold(false);
        painter->setFont(font);
        painter->drawText(option.rect, Qt::AlignCenter|Qt::AlignVCenter,index.data().toString());
    }

    if (index.data(Qt::UserRole).toString() == "value" ) // Value
    {
        painter->setBrush(QColor("#DAF2FB"));
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(bgRect,5,5);
        painter->setPen(QColor("#4183B0"));
        font.setBold(false);
        painter->setFont(font);
        painter->drawText(bgRect, Qt::AlignCenter|Qt::AlignVCenter,index.data().toString());
    }


    // return QStyledItemDelegate::paint(painter, option, index);

}






QSize FilterDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option,index);
    size.setHeight(25);

    return size;
}
