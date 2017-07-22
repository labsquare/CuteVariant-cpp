#include "mainwindow.h"
#include "project.h"

using namespace core;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    mView    = new QTreeView;
    mEditor  = new QueryEditor;
    mProject = new core::Project("/tmp/variant.db");
    mModel   = new core::ResultModel(mProject);
    mFieldModel = new core::FieldsModel(mProject);

//   mProject->importFile("/tmp/TRIO1.family.vcf");


    mView->setModel(mModel);

    setCentralWidget(mView);

    QDockWidget * dock = new QDockWidget();
    dock->setWidget(mEditor);
    addDockWidget(Qt::BottomDockWidgetArea, dock);

    // tmp test
    QTreeView * fieldView = new QTreeView;
    fieldView->setModel(mFieldModel);
    QDockWidget * dock2 = new QDockWidget();
    dock2->setWidget(fieldView);

    addDockWidget(Qt::BottomDockWidgetArea, dock2);
    addDockWidget(Qt::BottomDockWidgetArea, dock);



    mEditor->setPlainText("SELECT qual FROM variants");
    connect(mEditor, &QueryEditor::returnPressed, mModel, [this](){mModel->setQuery(mEditor->toPlainText());});


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
