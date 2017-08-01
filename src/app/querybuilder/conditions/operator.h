#ifndef OPERATOR_H
#define OPERATOR_H
#include <QtCore>

class Operator
{
public:

    Operator();
    Operator(const QString& name, const QString& symbol);
    QString name() const;
    QString symbol() const;

private:
    QString mName;
    QString mSymbol;


};

#endif // OPERATOR_H
