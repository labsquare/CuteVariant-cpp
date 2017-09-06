#ifndef COLUMNVIEW_H
#define COLUMNVIEW_H
#include <QtWidgets>
#include "columnmodel.h"
#include "project.h"

class ColumnView : public QTreeView
{
    Q_OBJECT
public:
    ColumnView(QWidget * parent = nullptr);
    QStringList selectedColumns() const;

    void load();


private:
    ColumnModel * mModel;
};

#endif // COLUMNVIEW_H
