#include "columndockwidget.h"

ColumnDockWidget::ColumnDockWidget(QWidget * parent):
    BaseDockWidget(parent)
{
    mView       = new ColumnView();
    mSearchEdit = new QLineEdit();


    mSearchEdit->setVisible(false);

    setTitle("Fields");

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(mView);
    mainLayout->addWidget(mSearchEdit);
    QWidget * mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);


    setWidget(mainWidget);


    addAction(FIcon(0xf616),"Expand", mView, SLOT(expandAll()));
    addAction(FIcon(0xf615),"Collapse", mView, SLOT(collapseAll()));

    // create search action
    QAction * findAction = new QAction(FIcon(0xf349),"Find",this);
    findAction->setCheckable(true);
    addAction(findAction);
    connect(findAction, &QAction::toggled, [this](bool a) {
        mSearchEdit->setVisible(a);
        if (a)
        {
            mView->expandAll();
            mSearchEdit->setFocus();
        }
        else {
            mSearchEdit->clear();
            mView->collapseAll();
        }

    });

    // addAction(FIcon(0xf140),"test", mView, SLOT(collapseAll()));

    addActionSpacer();
    //addAction(FIcon(0xf5e8),"Clear", mView, SLOT(clearSelection()));

    // addAction(FIcon(0xf118),"Collapse", mView, SLOT(collapseAll()));


    // emit changed signal when model changed
    connect(mView, &ColumnView::itemChanged,[this](){emit changed();});
    connect(mView,SIGNAL(filterItemCreated(ConditionItem*)),this,SIGNAL(filterItemCreated(ConditionItem*)));
    connect(mSearchEdit,SIGNAL(textChanged(QString)),mView,SLOT(setFilter(QString)));

}
QStringList ColumnDockWidget::selectedColumns() const
{
    return mView->selectedColumns();
}

void ColumnDockWidget::reset()
{
    mView->load();

}
