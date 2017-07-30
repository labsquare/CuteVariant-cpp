#include "querybuilderwidget.h"


QueryBuilderWidget::QueryBuilderWidget(core::Project *prj, QWidget *parent)
    :QWidget(parent), mProject(prj)
{
    mBar         = new QToolBar;
    mStack       = new QStackedWidget;
    mMenuButton  = new QPushButton();


    // ======  Create toolbar
    mMenuButton->setFlat(true);
    mMenuButton->setMenu(new QMenu());
    mBar->addWidget(mMenuButton);
    // add spacer
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mBar->addWidget(spacer);
    connect(mMenuButton->menu(),SIGNAL(triggered(QAction*)),this,SLOT(changeWidget(QAction*)));

    // merge layout
    QVBoxLayout * mLayout = new QVBoxLayout;
    mLayout->addWidget(mBar);
    mLayout->addWidget(mStack);
    mLayout->setContentsMargins(0,4,0,0);
    mLayout->setSpacing(0);
    setLayout(mLayout);


    // add Column widget
    //    addWidget(new ColumnView(prj));


    mSelectionView = new SelectionView(mProject);
    addWidget(mSelectionView);

    mColumnView = new ColumnView(mProject);
    addWidget(mColumnView);

    mLogicView = new LogicView(mProject);
    addWidget(mLogicView);



    //    // add table model
    //    QTableView * tableView = new QTableView;
    //    tableView->setWindowTitle("Table");
    //    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //    tableView->verticalHeader()->hide();
    //    mTableModel = new TableModel(mProject);
    //    tableView->setModel(mTableModel);
    //    tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //    tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    //    addWidget(tableView);

    //    // add logic view
    //    mLogicView = new LogicView;
    //    addWidget(mLogicView);

    changeWidget(mMenuButton->menu()->actions().first());

}

core::VariantQuery QueryBuilderWidget::query() const
{
    core::VariantQuery q;
    q.setColumns(mColumnView->selectedColumns());
    q.setTable(mSelectionView->tableName());
    q.setCondition(mLogicView->query());

    return q;
}

void QueryBuilderWidget::updateQuery()
{
    //    builder->setColumns(mColumnView->selectedColumns());
    //    builder->setTableName("variants");
    //    builder->setCondition(mLogicView->query());

}

void QueryBuilderWidget::load()
{

    mColumnView->load();
    mSelectionView->load();

}

void QueryBuilderWidget::addWidget(QWidget *w)
{
    mStack->addWidget(w);
    QAction * action = mMenuButton->menu()->addAction(w->windowIcon(), w->windowTitle());
    mWidgets[action] = w;

}

void QueryBuilderWidget::changeWidget(QAction *action)
{

    if (mWidgets.contains(action))
    {
        mStack->setCurrentWidget(mWidgets[action]);
        mMenuButton->setText(action->text());

        // clear previously actions bar
        for (QAction * a: mBar->actions()){
            if (a->metaObject()->className() != QWidgetAction::staticMetaObject.className())
                mBar->removeAction(a);
        }

        mBar->addActions(mWidgets[action]->actions());

    }

}
