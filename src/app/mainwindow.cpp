#include "mainwindow.h"
#include "project.h"
#include "columndockwidget.h"
#include "linklistdialog.h"
#include "filterwidget.h"
using namespace cvar;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{


    // Variant query editor
    mEditor                = new VqlEditor();

    // Main result view
    mResultsView           = new ResultsView();
    mResultTab             = new QTabWidget();
    // dock widget
    mColumnDock       = new ColumnDockWidget();
    mSelectionDock    = new SelectionDockWidget();
    mFilterDock       = new FilterDockWidget();
    mBedDock          = new BedDockWidget();

    mLocationSearchEdit = new QLineEdit;

    addBaseDock(mColumnDock);
    addBaseDock(mSelectionDock);
    addBaseDock(mFilterDock);
    addBaseDock(mBedDock);
    //addBaseDock(new MetadataDockWidget);


    // setup central widget
    QSplitter * mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(mResultTab);
    mainSplitter->addWidget(mEditor);
    setCentralWidget(mainSplitter);
    mResultTab->setTabsClosable(true);
    mResultTab->setTabPosition(QTabWidget::North);


    // add defaut view
    addResultView(new ResultsView("variants"));

    // setup toolbox
    mToolBar = addToolBar("main");
    mToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mToolBar->setFloatable(false);
    mToolBar->setMovable(false);


    // install actions
    setupActions();


    //connection
    //exec
    connect(mEditor,&VqlEditor::returnPressed, this, &MainWindow::execute);

    // columns create filter => to filter
    connect(mColumnDock,SIGNAL(filterItemCreated(ConditionItem*)),mFilterDock, SLOT(addCondition(ConditionItem*)));
    connect(mResultTab, &QTabWidget::tabCloseRequested, [this](int index){  mResultTab->removeTab(index); });
    connect(mSelectionDock,SIGNAL(selectionDoubleClicked(QString)), this,SLOT(executeSelection(QString)));

    setStatusBar(new QStatusBar());

    // For Dev testing
    //cutevariant->setDatabasePath("/tmp/test.vcf.db");

    restoreSettings();
//    reset();

    setDockOptions(QMainWindow::VerticalTabs);

}
//-------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    writeSettings();
}
//-------------------------------------------------------------------------

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());

    settings.endGroup();
}
//-------------------------------------------------------------------------

void MainWindow::restoreSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());

    settings.endGroup();
}
//-------------------------------------------------------------------------

void MainWindow::importFile()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Import File"),QDir::homePath(),tr("Images (*.vcf *.vcf.gz)"));
    if (filename.isEmpty())
        return;

    QString dbPath = filename + ".db";
    if (QFile::exists(dbPath))
    {
        int ret = QMessageBox::warning(this,
                                       tr("Warning"),
                                       tr("one database already exists. Do you want to remove it ?"),
                                       QMessageBox::Ok|QMessageBox::Cancel);
        if (ret == QMessageBox::Ok)
            QFile::remove(dbPath);
        else
            return;
    }

    cutevariant->setDatabasePath(dbPath);
    ImportDialog dialog;
    dialog.setFilename(filename);

    if (dialog.exec())
        reset();

}

//-------------------------------------------------------------------------

void MainWindow::closeEvent(QCloseEvent *)
{
    writeSettings();
}
//-------------------------------------------------------------------------

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open DB file"), QDir::homePath(), tr("DB Extension (*.db)"));
    if (!fileName.isEmpty())
    {
        cutevariant->setDatabasePath(fileName);
        reset();
        statusBar()->showMessage(fileName);
        return;

    }
}
//-------------------------------------------------------------------------
void MainWindow::saveFile()
{

}
//-------------------------------------------------------------------------
void MainWindow::addResultView(ResultsView *view)
{
    mResultTab->addTab(view, view->windowIcon(), view->name());
    mResultTab->setCurrentWidget(view);
    connect(view, &ResultsView::tableSaved, mSelectionDock, &SelectionDockWidget::reset);

}
//-------------------------------------------------------------------------

ResultsView *MainWindow::currentResultView()
{
    if (mResultTab->count() == 0)
        addResultView(new ResultsView("variants"));

    ResultsView * view = qobject_cast<ResultsView*>(mResultTab->currentWidget());
    return view;
}
//-------------------------------------------------------------------------
void MainWindow::execute()
{
    if (mEditor->isValid())
    {

        QString vql    = mEditor->toVql();
        VariantQuery q = VariantQuery::fromVql(vql);
        currentResultView()->setQuery(q);

    }
}
//-------------------------------------------------------------------------
void MainWindow::executeSelection(const QString &name)
{

    addResultView(new ResultsView(name));

    VariantQuery q;
    q.setColumns(mColumnDock->selectedColumns());
    q.setTable(name);
    q.setCondition(mFilterDock->condition());
    currentResultView()->setQuery(q);

}
//-------------------------------------------------------------------------
void MainWindow::updateEditor()
{
    mEditor->setVql(
                mColumnDock->selectedColumns(),
                mSelectionDock->tableName(),
                mFilterDock->condition(),
                mBedDock->region()
                );

    execute();

}
//-------------------------------------------------------------------------
void MainWindow::reset()
{
    mEditor->reset();

    for (BaseDockWidget * w : mBaseDocks)
        w->reset();

    execute();

}
//-------------------------------------------------------------------------

void MainWindow::addBaseDock(BaseDockWidget *widget)
{
    widget->setObjectName(widget->metaObject()->className());
    addDockWidget(Qt::LeftDockWidgetArea,widget);
    connect(widget, &BaseDockWidget::changed, this, &MainWindow::updateEditor);
    mBaseDocks.append(widget);
}
//-------------------------------------------------------------------------
void MainWindow::setupActions()
{

    //    QAction * importAction = mToolBar->addAction(QIcon::fromTheme("document-import"),tr("Import"),this, SLOT(importFile()));
    //    QAction * openAction   = mToolBar->addAction(QIcon::fromTheme("document-open"),tr("Open"),this, SLOT(openFile()));
    //   // QAction * saveAction   = bar->addAction(QIcon::fromTheme("document-open"),tr("Save"),this, SLOT(saveFile()));
    //    QAction * runAction    = mToolBar->addAction(QIcon::fromTheme("run-build"),tr("Run"),this,SLOT(execute()));

    //    QAction * showConsole = new QAction(QIcon::fromTheme("console"),tr("Show console"),this);
    //    showConsole->setCheckable(true);
    //    showConsole->setChecked(true);
    //    connect(showConsole,SIGNAL(triggered(bool)), mEditor, SLOT(setVisible(bool)));
    //    mToolBar->addAction(showConsole);


    // setup menu bar
    setMenuBar(new QMenuBar);
    QMenu * fileMenu = menuBar()->addMenu("&File");
    QAction * openAction   = fileMenu->addAction(FIcon(0xf116), "&Open ...", this, SLOT(openFile()), QKeySequence::Open);
    QAction * importAction = fileMenu->addAction(FIcon(0xf108), "&Import ...", this, SLOT(importFile()), QKeySequence::New);
    fileMenu->addSeparator();
    fileMenu->addAction(FIcon(0xf08b),"&Quit");

    QMenu * queryMenu = menuBar()->addMenu("&Query");
    QAction * runAction = queryMenu->addAction(FIcon(0xf126), "&Run", this, SLOT(execute()), QKeySequence(Qt::CTRL + Qt::Key_R));


    QMenu * columnMenu = queryMenu->addMenu("&Columns");
    columnMenu->addActions(mColumnDock->actions());

    QMenu * selectionMenu = queryMenu->addMenu("&Selection");
    selectionMenu->addActions(mSelectionDock->actions());

    QMenu * filterMenu = queryMenu->addMenu("&Columns");
    filterMenu->addActions(mFilterDock->actions());






    // setup toolbar
    mToolBar->addAction(openAction);
    mToolBar->addAction(importAction);
    mToolBar->addAction(runAction);

    // TEST
//    mToolBar->addAction(queryMenu->addAction(FIcon(0xf12f), "&test", this, SLOT(execute()), QKeySequence(Qt::CTRL + Qt::Key_R)));
//    mToolBar->addAction(queryMenu->addAction(FIcon(0xf134), "&test", this, SLOT(execute()), QKeySequence(Qt::CTRL + Qt::Key_R)));
//    mToolBar->addAction(queryMenu->addAction(FIcon(0xf146), "&test", this, SLOT(execute()), QKeySequence(Qt::CTRL + Qt::Key_R)));


    // add search bar
    QWidget * spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
   // mToolBar->addWidget(spacer);
   // mToolBar->addWidget(mLocationSearchEdit);
  //  mLocationSearchEdit->setMinimumWidth(300);

  //  mLocationSearchEdit->addAction(new QAction(FIcon(0xf118),"search"), QLineEdit::LeadingPosition);


}
