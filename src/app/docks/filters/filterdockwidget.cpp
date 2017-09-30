#include "filterdockwidget.h"

FilterDockWidget::FilterDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{
    mView = new FilterView;
    setTitle("Filter");
    setWidget(mView);


    addAction(FIcon(0xf126), "add logic", this, SLOT(addLogic()));
    addAction(FIcon(0xf067), "add condition", this, SLOT(addCondition()));
    addAction(FIcon(0xf1f8), "remove", this, SLOT(remove()));


    QAction * saveAction = new QAction(FIcon(0xf115),"open");
    saveAction->setMenu(new QMenu);
    saveAction->menu()->addAction("Preset1");
    saveAction->menu()->addAction("Preset2");
    saveAction->menu()->addAction("Preset3");
    saveAction->menu()->addSeparator();
    saveAction->menu()->addAction("Save");
    saveAction->menu()->addAction("Edit ...");


    addAction(saveAction);



    // create actions
    //   QAction *logicAction = new QAction(QIcon::fromTheme("list-add"), "add logic",this);
    //   QAction *condAction  = new QAction(QIcon::fromTheme("list-add"), "add condition",this);
    //    QAction *delAction   = new QAction(QIcon::fromTheme("list-remove"), "remove(s)",this);

    //    addAction(logicAction);
    //    addAction(condAction);
    //    addAction(delAction);

    //    // connect actions
    //    connect(logicAction,&QAction::triggered, [this](){mView->addLogic(); emit changed(); });
    //    connect(condAction,&QAction::triggered,[this](){mView->addCondition();emit changed();});
    //    connect(delAction,&QAction::triggered, [this](){mView->removeSelections();emit changed();});



}

QString FilterDockWidget::condition() const
{
    return mView->query();
}

void FilterDockWidget::addCondition(FilterItem *item)
{
    mView->addCondition(item);
    emit changed();


}

void FilterDockWidget::addCondition()
{
    AllFilterDIalog dialog(this);
    if (dialog.exec())
        addCondition(dialog.filterItem());
}

void FilterDockWidget::addLogic()
{
    mView->addLogic();
    emit changed();


}

void FilterDockWidget::remove()
{

    int ret = QMessageBox::information(this,"supression","Are you sure you want to delete the table ? ", QMessageBox::Ok|QMessageBox::Cancel);

    if (ret == QMessageBox::Ok)
    {
        mView->removeSelections();
        emit changed();
    }


}


