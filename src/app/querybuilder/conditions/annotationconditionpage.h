#ifndef ANNOTATIONCONDITIONPAGE_H
#define ANNOTATIONCONDITIONPAGE_H
#include <QtWidgets>
#include "project.h"
#include "conditionfieldfactory.h"
#include "listfieldwidget.h"
#include "rangefieldwidget.h"
#include "conditionalitem.h"

class AnnotationConditionPage : public QWidget
{
    Q_OBJECT
public:
    explicit AnnotationConditionPage(QWidget *parent = 0);

    ConditionalItem * toItem() const;
    void fromItem(ConditionalItem * item);


protected:
    void loadFields();

protected Q_SLOTS:
    void loadOperators();
    void loadForm();



private:
    QComboBox * mFieldbox;
    QComboBox * mOperatorBox;
    QLabel * mDescription;
    QList<cvar::Field> mFields;
    QFormLayout * mFormLayout;
    AbstractFieldWidget * mValueWidget;




};

#endif // ANNOTATIONCONDITIONPAGE_H
