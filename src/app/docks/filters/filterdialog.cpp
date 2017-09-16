#include "filterdialog.h"

FilterDialog::FilterDialog(QWidget *parent)
{

    mBox = new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel, Qt::Horizontal, this);
    mTabWidget = new QTabWidget(this);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addWidget(mTabWidget);
    vLayout->addWidget(mBox);
    setLayout(vLayout);

    addWidget(new AnnotationConditionPage());
    addWidget(new GenotypeConditionPage());


    connect(mBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(mBox,SIGNAL(rejected()),this,SLOT(reject()));



}


void FilterDialog::addWidget(QWidget *w)
{

    mTabWidget->addTab(w, w->windowIcon(), w->windowTitle());


}

FilterItem *FilterDialog::toItem()
{
    return qobject_cast<AnnotationConditionPage*>(mTabWidget->widget(0))->toItem();
}

void FilterDialog::fromItem(FilterItem *item)
{
   qobject_cast<AnnotationConditionPage*>(mTabWidget->widget(0))->fromItem(item);

}
