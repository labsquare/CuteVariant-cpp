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

    // dock widget
    mColumnDock       = new ColumnDockWidget();
    mSelectionDock    = new SelectionDockWidget();
    mConditionDock    = new FilterDockWidget();

    addBaseDock(mColumnDock);
    addBaseDock(mSelectionDock);
    addBaseDock(mConditionDock);


    // setup central widget
    QSplitter * mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(mResultsView);
    mainSplitter->addWidget(mEditor);
    setCentralWidget(mainSplitter);

    // setup toolbox
    QToolBar * bar = addToolBar("main");
    bar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    bar->setFloatable(false);
    bar->setMovable(false);
    bar->addAction(QIcon::fromTheme("document-import"),tr("Import"),this, SLOT(importFile()));
    bar->addAction(QIcon::fromTheme("document-open"),tr("Open"),this, SLOT(openFile()));
    bar->addAction(QIcon::fromTheme("document-open"),tr("Save"),this, SLOT(saveFile()));
    bar->addAction(QIcon::fromTheme("run-build"),tr("Play"),this,SLOT(execute()));


    //connection
    //exec
    connect(mEditor,&VqlEditor::returnPressed, this, &MainWindow::execute);

    // update selection
    connect(mResultsView, &ResultsView::tableSaved, mSelectionDock, &SelectionDockWidget::reset);

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

    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::homePath(),tr("Images (*.vcf)"));
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
void MainWindow::execute()
{

    if (mEditor->isValid())
    {

        QString vql    = mEditor->toVql();
        VariantQuery q = VariantQuery::fromVql(vql);
        mResultsView->setQuery(q);

    }
}
//-------------------------------------------------------------------------
void MainWindow::updateEditor()
{
    mEditor->setVql(
                mColumnDock->selectedColumns(),
                mSelectionDock->tableName(),
                mConditionDock->condition()
                );

}
//-------------------------------------------------------------------------
void MainWindow::reset()
{

    for (BaseDockWidget * w : mBaseDocks)
        w->reset();

}
//-------------------------------------------------------------------------

void MainWindow::addBaseDock(BaseDockWidget *widget)
{
    addDockWidget(Qt::LeftDockWidgetArea,widget);
    connect(widget, &BaseDockWidget::changed, this, &MainWindow::updateEditor);
    mBaseDocks.append(widget);
}
