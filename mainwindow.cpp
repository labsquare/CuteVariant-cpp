#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    Project * prj = new Project("/home/sacha/Dev/CuteVariant/variant.db");

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


    mFieldView->update();

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

void MainWindow::createActions()
{

    QToolBar * bar = addToolBar("act");
    bar->addAction("Run",this,SLOT(run()));


}
