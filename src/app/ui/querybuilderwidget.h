#ifndef QUERYBUILDERWIDGET_H
#define QUERYBUILDERWIDGET_H
#include <QtWidgets>
#include "project.h"
#include "logicview.h"
#include "columnview.h"
#include "tablemodel.h"
#include "variantquery.h"

class QueryBuilderWidget : public QWidget
{
    Q_OBJECT
public:
    QueryBuilderWidget(core::Project * prj, QWidget * parent = nullptr);

    core::VariantQuery query() const;


public Q_SLOTS:
    void updateQuery();
    void load();

protected Q_SLOTS:
    void addWidget(QWidget * w);
    void changeWidget(QAction * action);


private:
    core::Project * mProject;
    QToolBar * mBar;
    QPushButton * mMenuButton;
    QStackedWidget * mStack;
    QHash<QAction*, QWidget*> mWidgets;

    ColumnView * mColumnView;
    LogicView * mLogicView;


};

#endif // QUERYBUILDERWIDGET_H
