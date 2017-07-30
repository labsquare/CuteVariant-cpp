#ifndef RESULTSVIEW_H
#define RESULTSVIEW_H

#include <QtWidgets>
#include "resulttreemodel.h"
#include "project.h"
#include "qfonticon.h"
#include "variantquery.h"

class ResultsView : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsView(core::Project * prj, QWidget *parent = nullptr);

public Q_SLOTS:
    void setQuery(const core::VariantQuery& query);

protected Q_SLOTS:
    void pageUp();
    void pageDown();
    void pageFirst();
    void pageLast();
    void setPage(int page);

protected:
    void contextMenuEvent(QContextMenuEvent * event);
    void setupToolbar();



private:
    QTreeView * mView;
    ResultTreeModel * mModel;
    core::Project * mPrj;
    QToolBar * mTopToolBar;
    QToolBar * mBottomToolBar;
    QLineEdit * mPageBox;
    QLabel * mCountLabel;
    QIntValidator * mPageValidator;
};

#endif // RESULTSVIEW_H
