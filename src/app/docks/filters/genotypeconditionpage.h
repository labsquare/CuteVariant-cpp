#ifndef GENOTYPECONDITIONPAGE_H
#define GENOTYPECONDITIONPAGE_H
#include <QtWidgets>
#include "project.h"
#include "filterfieldfactory.h"

class GenotypeConditionPage : public QWidget
{
    Q_OBJECT
public:
    explicit GenotypeConditionPage(QWidget * parent = nullptr);

protected Q_SLOTS:
    void loadSamples();
    void loadFields();
    void loadOperators();
    void loadForm();


private:
    QComboBox * mSampleBox;
    QComboBox * mFieldBox;
    QComboBox * mOperatorBox;
    QFormLayout * mFormLayout;

    QList<cvar::Field> mFields;
};

#endif // GENOTYPECONDITIONPAGE_H
