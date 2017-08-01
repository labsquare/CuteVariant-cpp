#ifndef CONDITIONFIELDFACTORY_H
#define CONDITIONFIELDFACTORY_H

#include <QtSql>
#include <QtCore>
#include "operator.h"
#include "field.h"
#include "abstractfield.h"
#include "boolfield.h"
#include "stringfield.h"
#include "integerfield.h"
#include "doublefield.h"
#include "listfield.h"

class ConditionFieldFactory
{
public:
    ConditionFieldFactory();
    static AbstractField * widget(const cvar::Field& field);
    static QList<Operator> operatorsList(const cvar::Field& field);


private:


};

#endif // CONDITIONFIELDFACTORY_H
