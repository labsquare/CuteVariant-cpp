#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>
#include "resultmodel.h"
#include "queryeditor.h"
#include "querybuilderwidget.h"
#include "importdialog.h"

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
    void importFile();
    void openFile();
    void saveFile();

private:
    QString mCurrentFile;
    QString mCurrentDBFile;

    QTreeView * mView;
    QueryEditor * mEditor;
    core::Project * mProject;
    core::ResultModel * mResultModel;
    QueryBuilderWidget * mQueryBuilderWidget;



};

#endif // MAINWINDOW_H
