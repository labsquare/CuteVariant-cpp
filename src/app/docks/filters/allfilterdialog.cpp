#include "allfilterdialog.h"

AllFilterDIalog::AllFilterDIalog(QWidget *parent)
    :QDialog(parent)
{

    mView   = new QTreeView;
    mModel  = new ColumnModel;
    mWidget = new FilterWidget;
    mView->setModel(mModel);

    QDialogButtonBox * buttons = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

    QSplitter * splitter = new QSplitter(Qt::Horizontal);

    splitter->addWidget(mView);
    splitter->addWidget(mWidget);


    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);
    mainLayout->addWidget(buttons);

    setLayout(mainLayout);


    mWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mModel->setCheckBox(false);
    mModel->load();

    connect(mView,SIGNAL(clicked(QModelIndex)),this,SLOT(fieldSelected()));
    connect(buttons,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttons, SIGNAL(rejected()),this,SLOT(reject()));

}

ConditionItem *AllFilterDIalog::filterItem() const
{
    return mWidget->createCondition();
}

void AllFilterDIalog::fieldSelected()
{
    const cvar::Field field = mModel->field(mView->currentIndex());
    if (!field.isNull())
    {
        mWidget->setField(field);
    }


}
