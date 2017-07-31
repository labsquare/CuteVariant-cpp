#include "logicdelegate.h"

LogicDelegate::LogicDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{


}

QWidget * LogicDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{




    return QStyledItemDelegate::createEditor(parent, option, index);
}
