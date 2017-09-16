#include "filteritem.h"

FilterItem::FilterItem(const cvar::Field &field, Operator::Type op, const QVariant &value)
    :QStandardItem(), mField(field)
{

    setData(field.name(), FieldRole);
    setData(op, OperatorRole);
    setData(value, ValueRole);
    updateText();

    setEditable(false);
}



void FilterItem::setField(const cvar::Field &f)
{
    setData(f.name(),FieldRole);
    mField = f;
    updateText();
}

void FilterItem::setOperator(Operator::Type op)
{
    setData(op, OperatorRole);
    updateText();
}

void FilterItem::setValue(const QVariant &value)
{
    setData(value, ValueRole);
    updateText();
}

int FilterItem::type() const
{
    return FilterModel::ConditionalType;
}

const cvar::Field& FilterItem::field() const
{
    return mField;
}

QString FilterItem::operatorName() const
{
    return Operator::symbol(Operator::Type(data(OperatorRole).toInt()));
}

Operator::Type FilterItem::operatorType() const
{
    return Operator::Type(data(OperatorRole).toInt());
}

QVariant FilterItem::value() const
{
    return data(ValueRole);
}

void FilterItem::updateText()
{
    setText(QString("%1 %2 %3").arg(field().name()).arg(operatorName()).arg(value().toString()));
    setData(QString("%1 %2 '%3'").arg(field().colname()).arg(operatorName()).arg(value().toString()), ConditionRole);

}
