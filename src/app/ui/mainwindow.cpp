#include "mainwindow.h"
#include "project.h"

using namespace core;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mView               = new QTreeView;
    mEditor             = new QueryEditor;
    mProject            = new core::Project();
    mQueryBuilderWidget = new QueryBuilderWidget(mProject);
    mResultModel        = new core::ResultModel(mProject);

    //    mProject->importFile("/home/sacha/TRIO1.family.vcf");

    // setup widgets
    QSplitter * mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(mView);
    mainSplitter->addWidget(mEditor);
    mView->setModel(mResultModel);
    setCentralWidget(mainSplitter);

    QDockWidget * leftDock = new QDockWidget;
    leftDock->setWidget(mQueryBuilderWidget);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock);
    leftDock->setTitleBarWidget(new QWidget());


    mEditor->setPlainText("SELECT qual FROM variants");
    connect(mEditor, &QueryEditor::returnPressed, mResultModel, [this](){mResultModel->setQuery(mEditor->toPlainText());});


    // setup toolbox
    QToolBar * bar = addToolBar("main");

    bar->addAction(tr("Import"),this, SLOT(importFile()));
    bar->addAction(tr("Open"),this, SLOT(openFile()));
    bar->addAction(tr("Save"),this, SLOT(saveFile()));
    bar->addAction(tr("Reload"),this, SLOT(reload()));

    bar->addAction(tr("Play"), mQueryBuilderWidget, [this]()
    {
        mQueryBuilderWidget->buildQuery();
        mResultModel->load();
        statusBar()->showMessage(QString::number(mProject->sqliteManager()->variantQueryCount()));

    } );




}

MainWindow::~MainWindow()
{

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

    QFileInfo info(filename);
    mProject->setDatabasePath(info.dir().filePath(info.baseName()+".db"));


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
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Open VCF file"), QDir::homePath(), tr("VCF Extension (*.vcf);; Any Extension (*)"));
    if (!fileNames.isEmpty())
    {
        for (QString file : fileNames)
        {
            qDebug()<<"open only the first one";
            mCurrentFile = file;
            mCurrentDBFile = file +".db";
            QFile::remove(mCurrentDBFile);
            Project prj(mCurrentDBFile);
            prj.importFile(mCurrentFile);
            return;
        }
    }


}

void MainWindow::saveFile()
{

}

void MainWindow::reload()
{
    mQueryBuilderWidget->load();

}
