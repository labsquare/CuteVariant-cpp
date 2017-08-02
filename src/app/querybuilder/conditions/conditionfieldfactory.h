#ifndef CONDITIONFIELDFACTORY_H
#define CONDITIONFIELDFACTORY_H

#include <QtSql>
#include <QtCore>
#include "operator.h"
#include "field.h"
#include "abstractfieldwidget.h"
#include "boolfield.h"
#include "stringfieldwidget.h"
#include "integerfieldwidget.h"
#include "doublefieldwidget.h"
#include "listfieldwidget.h"

class ConditionFieldFactory
{
public:
    ConditionFieldFactory();
    static AbstractFieldWidget * widget(const cvar::Field& field);
    static QList<Operator::Type> operatorsList(const cvar::Field& field);


private:

    static QList<Operator>d;

};

#endif // CONDITIONFIELDFACTORY_H
