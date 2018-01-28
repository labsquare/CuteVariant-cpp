#include "filterdockwidget.h"

FilterDockWidget::FilterDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{
    mView = new FilterView;
    setTitle("Filter");
    setWidget(mView);

    mAddConditionAction = addAction(FIcon(0xf13b), "add condition", this, SLOT(addCondition()));
    mAddLogicAction     = addAction(FIcon(0xf138), "add logic", this, SLOT(addLogic()));
    mRemAction          = addAction(FIcon(0xf114), "remove", this, SLOT(remove()));

    addActionSpacer();
    QAction * saveAction = new QAction(FIcon(0xf11e),"open");
    saveAction->setMenu(new QMenu);
    saveAction->menu()->addAction("Preset1");
    saveAction->menu()->addAction("Preset2");
    saveAction->menu()->addAction("Preset3");
    saveAction->menu()->addSeparator();
    saveAction->menu()->addAction("Save");
    saveAction->menu()->addAction("Edit ...");
   // addAction(saveAction);
    updateActions();
    connect(mView,SIGNAL(activated(QModelIndex)), this, SLOT(updateActions()));
    connect(mView,SIGNAL(changed()),this,SIGNAL(changed()));

}


QString FilterDockWidget::condition() const
{
    return mView->query();
}

void FilterDockWidget::addCondition(ConditionItem *item)
{
    mView->addCondition(item);
}

void FilterDockWidget::addCondition()
{
    AllFilterDIalog dialog(this);
    if (dialog.exec())
        addCondition(dialog.filterItem());
}

void FilterDockWidget::addLogic()
{
    mView->addLogic(new LogicItem);


}

void FilterDockWidget::remove()
{

    int ret = QMessageBox::information(this,"supression","Are you sure you want to delete the table ? ", QMessageBox::Ok|QMessageBox::Cancel);

    if (ret == QMessageBox::Ok)
    {
        mView->removeSelections();
    }


}

void FilterDockWidget::updateActions()
{
    if (!mView->currentItem())
        return;

    if (mView->currentItem() == mView->topLevelItem(0))
        mRemAction->setDisabled(true);
    else
        mRemAction->setDisabled(false);


    if (mView->currentItem()->type() == FilterView::ConditionType)
    {
        mAddConditionAction->setDisabled(true);
        mAddLogicAction->setDisabled(true);
    }

    if (mView->currentItem()->type() == FilterView::LogicType)
    {
        mAddConditionAction->setEnabled(true);
        mAddLogicAction->setEnabled(true);
    }


}


