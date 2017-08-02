#ifndef OPERATOR_H
#define OPERATOR_H
#include <QtCore>

class Operator
{
public:
    enum Type{
        LessThan,
        LessThanOrEqualTo,
        MoreThan,
        MoreThanOrEqualTo,
        Equal,
        NotEqual,
        In,
        Between,
        Like
    };


    static QString symbol(Type type);
    static QString name(Type type);


private:
    Operator() {}
    static QHash<Type, QPair<QString, QString> > sMaps;


};

#endif // OPERATOR_H
