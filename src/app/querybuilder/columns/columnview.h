#ifndef COLUMNVIEW_H
#define COLUMNVIEW_H
#include <QtWidgets>
#include "columnmodel.h"
#include "project.h"

class ColumnView : public QTreeView
{
    Q_OBJECT
public:
    ColumnView(cvar::Project * prj, QWidget * parent = nullptr);
    QStringList selectedColumns() const;

public Q_SLOTS:
    void load();


private:
    cvar::Project * mProject;
    ColumnModel * mModel;
};

#endif // COLUMNVIEW_H
