#include "filterdockwidget.h"

FilterDockWidget::FilterDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{
    mView = new FilterView;
    setTitle("Filter");
    setWidget(mView);


    addAction(QIcon::fromTheme("list-add"), "add logic", this, SLOT(addLogic()));
    addAction(QIcon::fromTheme("list-add"), "add condition", this, SLOT(addCondition()));


    QAction * saveAction = new QAction(QIcon::fromTheme("folder-open"),"open");
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

void FilterDockWidget::addCondition()
{
    AllFilterDIalog dialog(this);
    if (dialog.exec())
    {

        mView->addCondition(dialog.filterItem());

        emit changed();
    }


}

void FilterDockWidget::addLogic()
{

}


