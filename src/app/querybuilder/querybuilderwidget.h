#ifndef QUERYBUILDERWIDGET_H
#define QUERYBUILDERWIDGET_H
#include <QtWidgets>
#include "project.h"
#include "logicview.h"
#include "columnview.h"
#include "selectionview.h"
#include "variantquery.h"

class QueryBuilderWidget : public QWidget
{
    Q_OBJECT
public:
    QueryBuilderWidget(QWidget * parent = nullptr);

    cvar::VariantQuery query() const;


public Q_SLOTS:
    void updateQuery();
    void load();

protected Q_SLOTS:
    void addWidget(QWidget * w);
    void changeWidget(QAction * action);


private:
    QToolBar * mBar;
    QPushButton * mMenuButton;
    QStackedWidget * mStack;
    QHash<QAction*, QWidget*> mWidgets;

    ColumnView * mColumnView;
    LogicView * mLogicView;
    SelectionView * mSelectionView;



};

#endif // QUERYBUILDERWIDGET_H
