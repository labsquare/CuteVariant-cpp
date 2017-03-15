#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "project.h"
#include "variantview.h"
#include "fieldview.h"
#include "logicview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void run();
    void open();


protected:
    void setDatabasePath(const QString& filename);
    void createActions();



private:
    VariantView * mVariantView;
    FieldView * mFieldView;
    LogicView * mLogicView;
    Project * mProject;
};

#endif // MAINWINDOW_H
