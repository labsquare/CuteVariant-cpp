#ifndef SELECTIONDOCKWIDGET_H
#define SELECTIONDOCKWIDGET_H

#include "basedockwidget.h"
#include "selectionview.h"
#include "operationsetdialog.h"
#include "searchitemview.h"

class SelectionDockWidget : public BaseDockWidget
{
    Q_OBJECT
public:
    SelectionDockWidget(QWidget *parent = 0);
    QString tableName() const;

public Q_SLOTS:
    void reset() override;
    void compare();

Q_SIGNALS:
    void selectionDoubleClicked(const QString& name);

private:
    SelectionView * mView;
    SearchItemView * mSearchView;
};

#endif // SELECTIONDOCKWIDGET_H
