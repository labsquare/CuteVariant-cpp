#include "operator.h"


QHash<Operator::Type, QPair<QString, QString> > Operator::sMaps =
{
    {Operator::LessThan, {"less than","<"}},
    {Operator::LessThanOrEqualTo, {"less than or equal to","<="}},
    {Operator::MoreThan, {"more than",">"}},
    {Operator::MoreThanOrEqualTo, {"more than or equal to",">="}},
    {Operator::Equal, {"equal to","="}},
    {Operator::NotEqual, {"not equal to","!="}},
    {Operator::In, {"in","IN"}},
    {Operator::Between, {"between","BETWEEN"}},
    {Operator::Like, {"like","LIKE"}},
    {Operator::And, {"and","AND"}},
    {Operator::Or, {"or","OR"}},
    {Operator::Union, {"union","UNION"}},
    {Operator::Intersect, {"intersect","INTERSECT"}},
    {Operator::Except, {"except","EXCEPT"}}
};

QString Operator::symbol(Operator::Type type)
{
    return sMaps[type].second;
}

QString Operator::name(Operator::Type type)
{
    return sMaps[type].first;

}
