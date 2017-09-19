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

    addBaseDock(mColumnDock);
    addBaseDock(mSelectionDock);
    addBaseDock(mFilterDock);
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
    connect(mColumnDock,SIGNAL(filterItemCreated(FilterItem*)),mFilterDock, SLOT(addCondition(FilterItem*)));
    connect(mResultTab, &QTabWidget::tabCloseRequested, [this](int index){  mResultTab->removeTab(index); });
    connect(mSelectionDock,SIGNAL(selectionDoubleClicked(QString)), this,SLOT(executeSelection(QString)));

    setStatusBar(new QStatusBar());

    // For Dev testing
    cutevariant->setDatabasePath("/tmp/test.vcf.db");

    restoreSettings();
    reset();


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
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}
//-------------------------------------------------------------------------

void MainWindow::restoreSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}
//-------------------------------------------------------------------------

void MainWindow::importFile()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::homePath(),tr("Images (*.vcf *.vcf.gz)"));
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
                mFilterDock->condition()
                );

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
    QAction * openAction   = fileMenu->addAction(FIcon(0xf115), "&Open ...", this, SLOT(openFile()), QKeySequence::Open);
    QAction * importAction = fileMenu->addAction(FIcon(0xf016), "&New ...", this, SLOT(importFile()), QKeySequence::New);
    fileMenu->addSeparator();
    fileMenu->addAction(FIcon(0xf08b),"&Quit");

    QMenu * queryMenu = menuBar()->addMenu("&Query");
    QAction * runAction = queryMenu->addAction(FIcon(0xf04b), "&Run", this, SLOT(execute()), QKeySequence(Qt::CTRL + Qt::Key_R));


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


}
