#include "operator.h"


Operator::Operator()
{

}

Operator::Operator(const QString &name, const QString &symbol)
    :mName(name), mSymbol(symbol)
{

}

QString Operator::name() const
{
    return mName;
}

QString Operator::symbol() const
{
    return mSymbol;
}

