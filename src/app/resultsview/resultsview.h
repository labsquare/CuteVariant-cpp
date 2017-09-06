#ifndef RESULTSVIEW_H
#define RESULTSVIEW_H

#include <QtWidgets>
#include "resulttreemodel.h"
#include "project.h"
#include "variantquery.h"

class ResultsView : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsView( QWidget *parent = nullptr);

public Q_SLOTS:
    void setQuery(const cvar::VariantQuery& query);


protected Q_SLOTS:
    void pageUp();
    void pageDown();
    void pageFirst();
    void pageLast();
    void setPage(int page);
    void save();
    void exportCsv();

Q_SIGNALS:
    void tableSaved();

protected:
    void contextMenuEvent(QContextMenuEvent * event);



private:
    QTreeView * mView;
    ResultTreeModel * mModel;
    QToolBar * mTopToolBar;
    QToolBar * mBottomToolBar;
    QLineEdit * mPageBox;
    QLabel * mCountLabel;
    QIntValidator * mPageValidator;

};

#endif // RESULTSVIEW_H
