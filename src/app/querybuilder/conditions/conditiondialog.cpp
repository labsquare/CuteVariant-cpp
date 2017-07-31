#include "conditiondialog.h"

ConditionDialog::ConditionDialog(cvar::Project *prj, QWidget *parent)
{

    mPrj = prj;
    mBox = new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel, Qt::Horizontal, this);
    mTabWidget = new QTabWidget(this);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mTabWidget);
    vLayout->addWidget(mBox);


    setLayout(vLayout);




}

void ConditionDialog::addWidget(QWidget *w)
{

    mTabWidget->addTab(w, w->windowIcon(), w->windowTitle());


}
