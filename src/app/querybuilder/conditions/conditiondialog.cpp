#include "conditiondialog.h"

ConditionDialog::ConditionDialog(QWidget *parent)
{

    mBox = new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel, Qt::Horizontal, this);
    mTabWidget = new QTabWidget(this);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mTabWidget);
    vLayout->addWidget(mBox);
    setLayout(vLayout);

    addWidget(new AnnotationConditionPage());
    addWidget(new GenotypeConditionPage());



}


void ConditionDialog::addWidget(QWidget *w)
{

    mTabWidget->addTab(w, w->windowIcon(), w->windowTitle());


}
