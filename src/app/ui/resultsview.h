#ifndef RESULTSVIEW_H
#define RESULTSVIEW_H

#include <QtWidgets>
#include "resultsmodel.h"
#include "project.h"
#include "qfonticon.h"

class ResultsView : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsView(core::Project * prj, QWidget *parent = nullptr);

public Q_SLOTS:
    void load();

protected Q_SLOTS:
    void pageUp();
    void pageDown();
    void pageFirst();
    void pageLast();
    void setPage(int page);

protected:
    void contextMenuEvent(QContextMenuEvent * event);


private:
    QTreeView * mView;
    ResultsModel * mModel;
    core::Project * mPrj;
    QToolBar * mTopToolBar;
    QToolBar * mBottomToolBar;
    QLineEdit * mPageBox;
    QLabel * mCountLabel;
    QIntValidator * mPageValidator;
};

#endif // RESULTSVIEW_H
