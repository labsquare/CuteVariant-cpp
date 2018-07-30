#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>
#include "project.h"

#include "resultsview.h"
#include "vqleditor.h"
#include "importdialog.h"

#include "columndockwidget.h"
#include "selectiondockwidget.h"
#include "filterdockwidget.h"
#include "metadatadockwidget.h"
#include "beddockwidget.h"
#include "chartdockwidget.h"
#include "qfonticon.h"

#include "importwizard.h"

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

    ResultsView * currentResultView();


public Q_SLOTS:
    // main tool bar actions
    void importFile();
    void openFile(const QString& filename = QString());
    void saveFile();
    void addResultView(ResultsView * view);



protected Q_SLOTS:

    /*!
     * @brief execute
     * execute the VQL query and update the view
     */
    void execute();

    /*!
     * @brief execute
     * execute the VQL query from a selection
     */
    void executeSelection(const QString& name);

    /*!
     * @brief refresh
     * update vql editor
     */
    void updateEditor();

    /*!
     * \brief reset
     * reset everything
     */
    void reset();


protected:
    void addBaseDock(BaseDockWidget * widget);
    void setupActions();

private:
    QString mCurrentFile;
    QString mCurrentDBFile;

    // central widgets
    VqlEditor * mEditor;
    ResultsView * mResultsView;
    QTabWidget * mResultTab;

    // dock widgets
    SelectionDockWidget * mSelectionDock;
    ColumnDockWidget * mColumnDock;
    FilterDockWidget * mFilterDock;
    RegionDockWidget * mRegionDock;
    ChartDockWidget * mChartDock;
    QList<BaseDockWidget*> mBaseDocks;
    QToolBar * mToolBar;
    QLineEdit * mLocationSearchEdit;





};

#endif // MAINWINDOW_H
