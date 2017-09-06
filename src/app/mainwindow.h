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
    // main tool bar actions
    void importFile();
    void openFile();
    void saveFile();


protected Q_SLOTS:

    /*!
     * @brief execute
     * execute the VQL query and update the view
     */
    void execute();

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

private:
    QString mCurrentFile;
    QString mCurrentDBFile;

    // central widgets
    VqlEditor * mEditor;
    ResultsView * mResultsView;

    // dock widgets
    SelectionDockWidget * mSelectionDock;
    ColumnDockWidget * mColumnDock;
    FilterDockWidget * mConditionDock;

    QList<BaseDockWidget*> mBaseDocks;




};

#endif // MAINWINDOW_H
