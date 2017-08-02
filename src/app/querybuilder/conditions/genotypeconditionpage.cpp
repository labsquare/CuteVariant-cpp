#include "genotypeconditionpage.h"

GenotypeConditionPage::GenotypeConditionPage(QWidget *parent)
    :QWidget(parent)
{

    mSampleBox   = new QComboBox;
    mFieldBox    = new QComboBox;
    mOperatorBox = new QComboBox;
    mFormLayout  = new QFormLayout;

    mFormLayout->addRow("Sample", mSampleBox);
    mFormLayout->addRow("fields", mFieldBox);
    mFormLayout->addRow("operator", mOperatorBox);



    setLayout(mFormLayout);
    setWindowTitle("Genotype fields");

    loadSamples();
    loadFields();

    connect(mFieldBox,SIGNAL(activated(int)),this,SLOT(loadOperators()));
    connect(mOperatorBox,SIGNAL(activated(int)),this,SLOT(loadForm()));

}

void GenotypeConditionPage::loadSamples()
{
    mSampleBox->clear();
    for (cvar::Sample s : cutevariant->sqliteManager()->samples())
    {
        mSampleBox->addItem(s.name(), s.id());
    }
}

void GenotypeConditionPage::loadFields()
{
    mFieldBox->clear();
    mFields = cutevariant->sqliteManager()->genotypeFields();
    for (cvar::Field f : mFields)
    {
        mFieldBox->addItem(f.name(), f.id());
    }

    loadOperators();
}

void GenotypeConditionPage::loadOperators()
{
    mOperatorBox->clear();

    for (Operator::Type type : ConditionFieldFactory::operatorsList(mFields[mFieldBox->currentIndex()]))
    {
        mOperatorBox->addItem(Operator::name(type), type);
    }

    loadForm();

}

void GenotypeConditionPage::loadForm()
{
    // the method avaible from Qt 5.8
    if (mFormLayout->rowCount() == 4)
        mFormLayout->removeRow(3);

    mFormLayout->insertRow(3,"Value", ConditionFieldFactory::widget(mFields[mFieldBox->currentIndex()]));


}
