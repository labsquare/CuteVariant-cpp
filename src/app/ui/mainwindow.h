#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>
#include "resultsview.h"
#include "queryeditor.h"
#include "querybuilderwidget.h"
#include "importdialog.h"
#include "locationlineedit.h"

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


protected Q_SLOTS:
    void reload();

private:
    QString mCurrentFile;
    QString mCurrentDBFile;

    QTreeView * mView;
    QueryEditor * mEditor;
    core::Project * mProject;
    ResultsView * mResultsView;
    QueryBuilderWidget * mQueryBuilderWidget;
    LocationLineEdit * mLocLineEdit;



};

#endif // MAINWINDOW_H
