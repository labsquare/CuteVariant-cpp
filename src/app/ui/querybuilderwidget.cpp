#include "querybuilderwidget.h"


QueryBuilderWidget::QueryBuilderWidget(core::Project *prj, QWidget *parent)
    :mProject(prj), QWidget(parent)
{
    mBar         = new QToolBar;
    mStack       = new QStackedWidget;
    mActionGroup = new QActionGroup(this);

    QVBoxLayout * mLayout = new QVBoxLayout;
    mLayout->addWidget(mBar);
    mLayout->addWidget(mStack);
    mLayout->setContentsMargins(0,0,0,0);
    mLayout->setSpacing(0);

    setLayout(mLayout);

    // add Column widget
    QTreeView * columnView = new QTreeView;
    mColumnModel = new ColumnModel(mProject);
    columnView->setModel(mColumnModel);
    addWidget(columnView);
    addWidget(new LogicView);





    mActionGroup->setExclusive(true);
    connect(mActionGroup, &QActionGroup::triggered, this, &QueryBuilderWidget::toolbarClicked);

}

void QueryBuilderWidget::addWidget(QWidget *w)
{

    QAction * action = mBar->addAction(w->windowIcon(),"A");
    action->setCheckable(true);
    mStack->addWidget(w);
    mWidgets[action] = w;
    mActionGroup->addAction(action);


}

void QueryBuilderWidget::toolbarClicked(QAction *action)
{

    if (mWidgets.contains(action))
    {
        mStack->setCurrentWidget(mWidgets[action]);
        action->setChecked(true);
    }

}
