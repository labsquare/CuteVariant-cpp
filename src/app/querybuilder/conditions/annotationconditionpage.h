#ifndef ANNOTATIONCONDITIONPAGE_H
#define ANNOTATIONCONDITIONPAGE_H
#include <QtWidgets>
#include "project.h"
#include "conditionfieldfactory.h"
#include "listfield.h"

class AnnotationConditionPage : public QWidget
{
    Q_OBJECT
public:
    explicit AnnotationConditionPage(QWidget *parent = 0);


protected:
    void loadFields();

protected Q_SLOTS:
    void fieldChanged(int index);



private:
    QComboBox * mFieldbox;
    QLabel * mDescription;
    QList<cvar::Field> mFields;
    QFormLayout * mFormLayout;




};

#endif // ANNOTATIONCONDITIONPAGE_H
