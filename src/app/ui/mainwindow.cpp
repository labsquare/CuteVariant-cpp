#include "mainwindow.h"
#include "project.h"

using namespace core;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mEditor             = new QueryEditor;
    mProject            = new core::Project();
    mQueryBuilderWidget = new QueryBuilderWidget(mProject);
    mResultsView        = new ResultsView(mProject);

    //    mProject->importFile("/home/sacha/TRIO1.family.vcf");

    // setup widgets
    QSplitter * mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(mResultsView);
    //mainSplitter->addWidget(mEditor);
    setCentralWidget(mainSplitter);

    QDockWidget * leftDock = new QDockWidget;
    leftDock->setWidget(mQueryBuilderWidget);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);
    leftDock->setTitleBarWidget(new QWidget());
    leftDock->setContentsMargins(0,0,0,0);

    //    setStyleSheet("QMainWindow::separator {"
    //                  "width: 10px;"
    //                  "height: 2px;"
    //                  "margin: -10px;"
    //                  "padding: 5px;}"
    //              );


    mEditor->setPlainText("SELECT qual FROM variants");
    //    connect(mEditor, &QueryEditor::returnPressed, mResultModel, [this](){mResultModel->setQuery(mEditor->toPlainText());});


    // setup toolbox
    QToolBar * bar = addToolBar("main");

    bar->addAction(tr("Import"),this, SLOT(importFile()));
    bar->addAction(tr("Open"),this, SLOT(openFile()));
    bar->addAction(tr("Save"),this, SLOT(saveFile()));
    bar->addAction(tr("Reload"),this, SLOT(reload()));

    bar->addAction(tr("Play"), mQueryBuilderWidget, [this]()
    {
        mQueryBuilderWidget->buildQuery();
        mResultsView->load();

    } );


    restoreSettings();

    mProject->setDatabasePath("/home/sacha/TRIO1.family.vcf.db");
    reload();

}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("currentFile", mCurrentFile);
    settings.setValue("currentDBFile", mCurrentFile);
    settings.endGroup();
}

void MainWindow::importFile()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Images (*.vcf)"));

    if (filename.isEmpty())
        return;

    QString dbPath = filename + ".db";

    if (QFile::exists(dbPath))
    {
        int ret = QMessageBox::warning(this, "Warning", "one database already exists. Do you want to remove it ?",QMessageBox::Ok|QMessageBox::Cancel );
        if (ret == QMessageBox::Ok)
            QFile::remove(dbPath);
        else
            return;
    }


    mProject->setDatabasePath(dbPath);


    ImportDialog dialog(mProject);
    dialog.setFilename(filename);

    if (dialog.exec())
    {
        reload();
    }






}


void MainWindow::restoreSettings()
{
    QSettings settings;
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    mCurrentFile = settings.value("currentFile", "").toString();
    mCurrentDBFile = settings.value("currentDBFile", "").toString();
    settings.endGroup();


    Project prj(mCurrentDBFile);
    prj.importFile(mCurrentFile);
}




void MainWindow::closeEvent(QCloseEvent *)
{
    writeSettings();
}


void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open DB file"), QDir::homePath(), tr("DB Extension (*.db)"));
    if (!fileName.isEmpty())
    {
        mProject->setDatabasePath(fileName);
        reload();
        return;

    }


}

void MainWindow::saveFile()
{

}

void MainWindow::reload()
{
    mQueryBuilderWidget->load();
    mResultsView->load();

}
