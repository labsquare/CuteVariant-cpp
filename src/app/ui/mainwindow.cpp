#include "mainwindow.h"
#include "project.h"

using namespace core;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mView    = new QTreeView;
    mQueryEdit =  new QLineEdit;
    mModel   = new core::ResultModel;
    mProject = new core::Project("/tmp/variant.db");

//    mProject->importFile("/tmp/TRIO1.family.vcf");

    mModel->setProject(mProject);

    mView->setModel(mModel);

    QToolBar * bar = addToolBar("query");
    bar->addWidget(mQueryEdit);


    setCentralWidget(mView);


    mQueryEdit->setText("SELECT qual FROM variants");
    connect(mQueryEdit, &QLineEdit::returnPressed, mModel, [this](){mModel->setQuery(mQueryEdit->text());});


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
