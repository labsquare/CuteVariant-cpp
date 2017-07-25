#include "querybuilderwidget.h"


QueryBuilderWidget::QueryBuilderWidget(core::Project *prj, QWidget *parent)
    :mProject(prj), QWidget(parent)
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

    connect(mMenuButton->menu(),SIGNAL(triggered(QAction*)),this,SLOT(toolbarClicked(QAction*)));

    // merge elements
    QVBoxLayout * mLayout = new QVBoxLayout;
    mLayout->addWidget(mBar);
    mLayout->addWidget(mStack);
    mLayout->setContentsMargins(0,4,0,0);
    mLayout->setSpacing(0);
    setLayout(mLayout);




    // add Column widget
    QTreeView * columnView = new QTreeView;
    columnView->setWindowTitle("Columns");
    mColumnModel = new ColumnModel(mProject);
    columnView->setModel(mColumnModel);
    addWidget(columnView);
    columnView->header()->hide();

    // add table model
    QTableView * tableView = new QTableView;
    tableView->setWindowTitle("Table");
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->verticalHeader()->hide();
    mTableModel = new TableModel(mProject);
    tableView->setModel(mTableModel);
    tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    addWidget(tableView);

    // add logic view
    mLogicView = new LogicView;
    addWidget(mLogicView);

    toolbarClicked(mMenuButton->menu()->actions().first());

}

void QueryBuilderWidget::buildQuery()
{
    core::QueryBuilder * builder = mProject->sqliteManager()->queryBuilder();

    builder->setColumns(mColumnModel->toColumns());
    builder->setTableName("variants");
    builder->setCondition(mLogicView->query());

}

void QueryBuilderWidget::load()
{
    mColumnModel->load();
    mTableModel->load();
}

void QueryBuilderWidget::addWidget(QWidget *w)
{
    mStack->addWidget(w);
    QAction * action = mMenuButton->menu()->addAction(w->windowIcon(), w->windowTitle());
    mWidgets[action] = w;

}

void QueryBuilderWidget::toolbarClicked(QAction *action)
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
