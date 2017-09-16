#include "logicitem.h"

LogicItem::LogicItem(const QString& op)
    :QStandardItem()
{

        setText(op);

}

int LogicItem::type() const
{
    return FilterModel::LogicType;
}
