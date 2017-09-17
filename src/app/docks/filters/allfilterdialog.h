#ifndef ALLFILTERDIALOG_H
#define ALLFILTERDIALOG_H
#include <QtWidgets>
#include "columnmodel.h"
#include "filterwidget.h"
class AllFilterDIalog : public QDialog
{
Q_OBJECT
public:
    AllFilterDIalog(QWidget * parent = nullptr);


protected Q_SLOTS:
    void fieldSelected();



private:
    QTreeView * mView;
    ColumnModel * mModel;
    FilterWidget * mWidget;

};

#endif // ALLFILTERDIALOG_H
