#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>
#include "resultmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

    // Overriden methods
    void closeEvent(QCloseEvent*);


    // Tools
    void restoreSettings();
    void writeSettings();

public Q_SLOTS:
    void openFile();

private:
    QString mCurrentFile;
    QString mCurrentDBFile;

    QTreeView * mView;
    QLineEdit * mQueryEdit;

    core::ResultModel * mModel;
    core::Project * mProject;



};

#endif // MAINWINDOW_H
