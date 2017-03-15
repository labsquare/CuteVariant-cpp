#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    mProject     = new Project;

    mVariantView = new VariantView;
    mFieldView   = new FieldView;
    mLogicView   = new LogicView;

    setCentralWidget(mVariantView);

    QDockWidget * fieldDock = new QDockWidget;
    fieldDock->setWidget(mFieldView);

    QDockWidget * logicDock = new QDockWidget;
    logicDock->setWidget(mLogicView);

    addDockWidget(Qt::LeftDockWidgetArea, fieldDock);
    addDockWidget(Qt::LeftDockWidgetArea, logicDock);


    resize(800,600);

    createActions();


}

MainWindow::~MainWindow()
{

}

void MainWindow::run()
{

    mVariantView->setCondition(mLogicView->query());
    mVariantView->setAnnotationColumns(mFieldView->selectedColNames());
    mVariantView->update();


}

void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open database"),
                                                    QDir::homePath(),
                                                    tr("Variant db (*.db *.vdb)"));
    if (!filename.isEmpty())
        setDatabasePath(filename);
}

void MainWindow::setDatabasePath(const QString &filename)
{
    mProject->setDatabasePath(filename);
    mProject->activate();

    mFieldView->refresh();
}

void MainWindow::createActions()
{

    QToolBar * bar = addToolBar("act");
    bar->addAction("Open",this,SLOT(open()));

    bar->addAction("Run",this,SLOT(run()));


}
