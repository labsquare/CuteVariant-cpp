#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>
#include "project.h"

#include "resultsview.h"
#include "vqleditor.h"
#include "querybuilderwidget.h"
#include "importdialog.h"
#include "locationlineedit.h"
#include "resulttreemodel.h"

#include "columndockwidget.h"

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
    void execute();
    void refresh();
    void reset();

private:
    QString mCurrentFile;
    QString mCurrentDBFile;


    QTreeView * mView;
    VqlEditor * mEditor;
    ResultsView * mResultsView;
    QueryBuilderWidget * mQueryBuilderWidget;
    LocationLineEdit * mLocLineEdit;

    ColumnDockWidget * columnDockWidget;

};

#endif // MAINWINDOW_H
