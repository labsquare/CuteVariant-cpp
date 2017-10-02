#include "logicitem.h"
#include "filterview.h"

LogicItem::LogicItem(LogicItem::LogicOperator op)
    :QTreeWidgetItem(FilterView::LogicType), mOperator(op)
{

    QFont font;
    font.setBold(true);
    setFont(0, font);

    setFlags(flags()|Qt::ItemIsEditable);

    updateItem();
}


QString LogicItem::name() const
{
    if (mOperator == LogicItem::Or)
        return "OR";
    else
        return "AND";
}

LogicItem::LogicOperator LogicItem::logic() const
{
    return mOperator;
}

void LogicItem::setLogic(LogicItem::LogicOperator op)
{
    mOperator = op;
    updateItem();
}

void LogicItem::updateItem()
{
    setText(0, name());
}
