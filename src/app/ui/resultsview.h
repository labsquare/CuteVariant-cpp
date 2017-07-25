#ifndef RESULTSVIEW_H
#define RESULTSVIEW_H

#include <QtWidgets>
#include "resultsmodel.h"
#include "project.h"

class ResultsView : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsView(core::Project * prj, QWidget *parent = nullptr);

public Q_SLOTS:
    void load();


private:
    QTreeView * mView;
    ResultsModel * mModel;
    core::Project * mPrj;
    QToolBar * mTopToolBar;
    QToolBar * mBottomToolBar;
    QSpinBox * mPageBox;
    QLabel * mCountLabel;
};

#endif // RESULTSVIEW_H
