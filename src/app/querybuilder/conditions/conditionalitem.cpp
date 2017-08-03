#include "conditionalitem.h"

ConditionalItem::ConditionalItem(const cvar::Field &field, Operator::Type op, const QVariant &value)
    :QStandardItem(), mField(field)
{

    setData(field.name(), FieldRole);
    setData(op, OperatorRole);
    setData(value, ValueRole);
    updateText();

    setEditable(false);
}



void ConditionalItem::setField(const cvar::Field &f)
{
    setData(f.name(),FieldRole);
    mField = f;
    updateText();
}

void ConditionalItem::setOperator(Operator::Type op)
{
    setData(op, OperatorRole);
    updateText();
}

void ConditionalItem::setValue(const QVariant &value)
{
    setData(value, ValueRole);
    updateText();
}

int ConditionalItem::type() const
{
    return FilterModel::ConditionalType;
}

const cvar::Field& ConditionalItem::field() const
{
    return mField;
}

QString ConditionalItem::operatorName() const
{
    return Operator::symbol(Operator::Type(data(OperatorRole).toInt()));
}

Operator::Type ConditionalItem::operatorType() const
{
    return Operator::Type(data(OperatorRole).toInt());
}

QVariant ConditionalItem::value() const
{
    return data(ValueRole);
}

void ConditionalItem::updateText()
{
    setText(QString("%1 %2 %3").arg(field().name()).arg(operatorName()).arg(value().toString()));
    setData(QString("%1 %2 '%3'").arg(field().colname()).arg(operatorName()).arg(value().toString()), ConditionRole);

}
