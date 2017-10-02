#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QtWidgets>
#include "operator.h"
#include "field.h"
#include "filterfieldfactory.h"
#include "rangefieldwidget.h"
#include "listfieldwidget.h"
#include "filteritem.h"

class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterWidget(QWidget *parent = nullptr);
    void setField(const cvar::Field& field);
    const cvar::Field& field() const;
    QVariant value() const;
    void setValue(const QVariant& value);

    Operator::Type currentOperator() const;

    void setCurrentOperator(Operator::Type type);

    ConditionItem * createCondition() const;

protected Q_SLOTS:
    void operatorChanged();

private:
    cvar::Field mField;
    QLabel * mNameLabel;
    QLabel * mDescLabel;
    QComboBox * mOperatorBox;
    QFormLayout * mFormLayout;
    AbstractFieldWidget * mFieldWidget = nullptr;



};

#endif // FILTERWIDGET_H
