#include "mainwindow.h"
#include "project.h"

using namespace core;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mEditor             = new QueryEditor;
    mProject            = new core::Project();
    mQueryBuilderWidget = new QueryBuilderWidget(mProject);
    mResultsView        = new ResultsView(mProject);
    mLocLineEdit        = new LocationLineEdit(mProject);


    // setup widgets
    QSplitter * mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(mResultsView);
    //mainSplitter->addWidget(mEditor);

    QSplitter * secondSplitter = new QSplitter(Qt::Horizontal);
    secondSplitter->addWidget(mQueryBuilderWidget);
    secondSplitter->addWidget(mainSplitter);
    secondSplitter->setStretchFactor(0, 20);
    secondSplitter->setStretchFactor(1, 80);

    setCentralWidget(secondSplitter);



    // setup toolbox
    QToolBar * bar = addToolBar("main");
    bar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    bar->setFloatable(false);
    bar->setMovable(false);

    bar->addAction(QIcon::fromTheme("document-import"),tr("Import"),this, SLOT(importFile()));
    bar->addAction(QIcon::fromTheme("document-open"),tr("Open"),this, SLOT(openFile()));
    bar->addAction(QIcon::fromTheme("document-save"),tr("Save"),this, SLOT(saveFile()));
    bar->addAction(QIcon::fromTheme("run-build"),tr("Play"),this,SLOT(refresh()));


    // add spacer
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bar->addWidget(spacer);
    bar->addWidget(mLocLineEdit);

    restoreSettings();

    mProject->setDatabasePath("/home/sacha/TRIO1.family.vcf.db");
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

    mProject->setDatabasePath(dbPath);
    ImportDialog dialog(mProject);
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
        mProject->setDatabasePath(fileName);
        reset();
        return;

    }
}
//-------------------------------------------------------------------------
void MainWindow::saveFile()
{

}
//-------------------------------------------------------------------------
void MainWindow::refresh()
{


    mResultsView->setQuery(mQueryBuilderWidget->query());



}
//-------------------------------------------------------------------------
void MainWindow::reset()
{

    mQueryBuilderWidget->load();
    //    mResultsView->setQuery();

}
