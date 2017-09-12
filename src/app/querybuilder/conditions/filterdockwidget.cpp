#include "filterdockwidget.h"

FilterDockWidget::FilterDockWidget(QWidget *parent)
    :BaseDockWidget(parent)
{
    mView = new FilterView;
    setTitle("Filter");
    setWidget(mView);


    // create actions
    QAction *logicAction = new QAction(QIcon::fromTheme("list-add"), "add logic",this);
    QAction *condAction  = new QAction(QIcon::fromTheme("list-add"), "add condition",this);
    QAction *delAction   = new QAction(QIcon::fromTheme("list-remove"), "remove(s)",this);

    addAction(logicAction);
    addAction(condAction);
    addAction(delAction);

    // connect actions
    connect(logicAction,&QAction::triggered, [this](){mView->addLogic(); emit changed(); });
    connect(condAction,&QAction::triggered,[this](){mView->addCondition();emit changed();});
    connect(delAction,&QAction::triggered, [this](){mView->removeSelections();emit changed();});



}

QString FilterDockWidget::condition() const
{
    return mView->query();
}

