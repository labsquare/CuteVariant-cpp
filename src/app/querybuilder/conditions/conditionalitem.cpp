#include "conditionalitem.h"

ConditionalItem::ConditionalItem(const QString &field, Operator::Type op, const QVariant &value)
    :QStandardItem()
{
    setData(field, FieldRole);
    setData(op, OperatorRole);
    setData(value, ValueRole);
    updateText();
}

void ConditionalItem::setField(const QString &f)
{
    setData(f, FieldRole);
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

QString ConditionalItem::field() const
{
    return data(FieldRole).toString();
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
   setText(QString("%1 %2 %3").arg(field()).arg(operatorName()).arg(value().toString()));
}
